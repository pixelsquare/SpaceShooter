#include "atom.h"
using namespace AtomEngine;

#define RANDOM_VALUE (rand() % 30) * 0.1f
#define RANDOM_COLOR (int)(rand() % 4)

enum GameMode {
	StartScreen,
	MainGame,
	CreditScreen
};
GameMode gameMode = StartScreen;

int score = 0;
int multiplier = 2;
float lifeColorOffset[3] = { 0.6f, 0.8f, 1.0f };

// Color properties used in enemy, turrets and bullets
// they share the same variable color;
struct ColorProperty 
{
	ColorProperty() 
    {
		this->color[0] = Color3::WHITE;
		this->color[1] = Color3::BLUE;
		this->color[2] = Color3::GREEN;
		this->color[3] = Color3::RED;
		this->size = (int)(sizeof(color) / sizeof(*color));
	}

	Color3 color[4];
	int size;
};

GameObject rocket[1];

class Enemy : public ColorProperty 
{
public:
	Enemy() 
    { 
		this->isAlive = true;
		this->life = 3;
		this->spawnPoint = Vector3f::ZERO;
		this->instance = new GameObject;

		this->explosion = new Particle;
		this->explosion->SetEnergy(10, 10);
		this->explosion->SetEmission(800, 800);
		this->explosion->SetEllipsoid(0.5f, 0.5f, 0.5f);
		this->explosion->SetRandomVelocity(5.0f, 5.0f, 5.0f);
		this->explosion->SetActiveParticle(false);

		this->particleColor[0] = Color3::WHITE;
		this->particleColor[1] = Color3::YELLOW;
	}

	void RenderEnemy() 
    {
		//this->instance->DrawPrimitive(AE_SOLID_CUBE);
		this->instance->DrawObject();
		this->explosion->EmitParticles();

		if(life <= 0) 
        {
            if(this->explosion->GetIsDestroyed())
            {
                this->isAlive = false;
            }
		}
	}

	void InitEnemy(Vector3f position) 
    {
		*this->instance = rocket[0];
		this->instance->SetPosition(position);
		this->instance->SetAcceleration(Vector3f::DOWN);
		this->instance->SetColor(this->color[RANDOM_COLOR]);
		//this->instance->SetScale(Vector3f::One * 0.5f);
		//this->instance->SetColliderSize(Vector3f::One * 0.5f);
		this->instance->SetActiveCollider(false);
	}

	void SubtractLife(int num) 
    {
		this->life -= num;
	}

	void EnemyExplode() 
    {
		this->instance->SetAcceleration(Vector3f::ZERO);
		this->instance->SetVelocity(Vector3f::ZERO);
		this->instance->SetActiveGameObject(false);
		this->instance->SetActiveCollider(false);
		this->instance->SetActiveCollision(false);

		this->particleColor[2] = this->color[RANDOM_COLOR];
		this->particleColor[3] = this->color[RANDOM_COLOR];
		this->explosion->SetColors(this->particleColor, 4);
		this->explosion->SetActiveParticle(true);
		this->explosion->SetAutoDestruct(true);
		this->explosion->SetPosition(this->instance->GetPosition());
	}

	bool GetAlive() 
    {
		return this->isAlive;
	}

	int GetLife() 
    {
		return this->life;
	}

	GameObject* instance;

private:
	bool isAlive;
	int life;
	Vector3f spawnPoint;

	Particle* explosion;
	Color3 particleColor[4];

protected:
};

class EnemySpawner 
{
public:
	EnemySpawner() 
    { 
		this->hasSpawned = false;
		this->yLimit = -8.0f;
		this->spawnDelay = 1.0f;
		this->tmpTime = 0.0f;
		this->spawnTime = new Time;
		this->spawnerPos = Vector3f::ZERO;
	}

	void RenderEnemies() 
    {
        if(!this->hasSpawned)
        {
            tmpTime = this->spawnDelay - this->spawnTime->LocalElapsedTime();
        }
        else
        {
            spawnTime->LocalReset();
        }

		if(!this->enemyInstance.empty()) 
        {
			for(int i = 0; i < this->enemyInstance.size(); i++) 
            {
				this->enemyInstance[i]->RenderEnemy();

                if(this->enemyInstance[i]->instance->GetPosition().y < this->yLimit)
                {
                    this->enemyInstance.erase(this->enemyInstance.begin() + i);
                }
			}

			spawnTime->LocalReset();
		}

		//ShowTimer();
	}

	void ShowTimer() 
    {
		if(!this->hasSpawned && tmpTime > 0) 
        {
			char text[100];
			sprintf(text, "%.1f", tmpTime);  
			Text::AddText2D(this->spawnerPos.x - 0.5f, this->spawnerPos.y - 1.5f, text, FontSize::MEDIUM_FONT);
		}
	}

	void SpawnEnemies() 
    {
		if(!this->hasSpawned && this->tmpTime <= 0.0f) 
        {
			CreateEnemy();
		}
	}

	void SetSpawnDelay(float delay) 
    {
		this->spawnDelay = delay;
	}

	void SetSpawnerPosition(Vector3f pos) 
    {
		this->spawnerPos = pos;
	}

	void RemoveEnemy(int indx) 
    {
		this->enemyInstance.erase(this->enemyInstance.begin() + indx);
	}

	void SetHasSpawned(bool spawn) 
    {
		this->hasSpawned = spawn;
	}

	bool GetHasSpawned() 
    {
		return this->hasSpawned;
	}

	std::vector<Enemy*> enemyInstance;

private:
	void CreateEnemy() 
    {
		this->hasSpawned = true;
		Enemy* tmpEnemy = new Enemy;
		tmpEnemy->InitEnemy(this->spawnerPos);
		this->enemyInstance.push_back(tmpEnemy);
		this->spawnDelay = 0.0f;
	}
	
	bool hasSpawned;
	float yLimit;
	float spawnDelay;
	float tmpTime;
	Time* spawnTime;
	Vector3f spawnerPos;

protected:

};

class Bullet : public ColorProperty 
{
public:
	Bullet() 
    { 
		this->posOffset = Vector3f::UP * 0.5f;
		this->yLimit = 8.0f;
	}

	void RenderBullet()
    {
		if(!this->bullet.empty()) 
        {
			for(int i = 0; i < this->bullet.size(); i++) 
            {
				this->bullet[i]->DrawPrimitive(AE_SOLID_SPHERE);

                if(bullet[i]->GetPosition().y > this->yLimit)
                {
                    bullet.erase(bullet.begin() + i);
                }
			}
		}
	}

	void SpawnBullet(Vector3f position, Color3 color) 
    {
		GameObject* tmpBullet = new GameObject;
		tmpBullet->SetPosition(position + posOffset);
		tmpBullet->SetColor(color);
		tmpBullet->SetScale(Vector3f::ONE * 0.2f);
		tmpBullet->SetColliderSize(Vector3f::ONE * 0.2f);
		tmpBullet->SetActiveCollider(false);
		tmpBullet->SetVelocity(Vector3f::UP);
		this->bullet.push_back(tmpBullet);
	}

	void RemoveBullet(int indx) 
    {
		this->bullet.erase(this->bullet.begin() + indx);
	}

private:
	Vector3f posOffset;
	float yLimit;

protected:
	std::vector<GameObject*> bullet;

};

class Turret : public Bullet 
{
public:
	Turret() 
    { 
		this->life = 2;
		this->clickCount = 0;
		this->buttonIndx = -1;
		this->tmpColorIndx = 0;
		this->curRot = 0.0f;
		this->nextRot = 0.0f;
		this->turnSpeed = 100;
		this->isMine = false;
		this->isAlive = true;
		this->instance = new GameObject;
	}

	void RenderTurret() 
    {
		// When firing bullet
		if(this->isMine && Input::GetKeyDown(' ')) 
        {
			this->SpawnBullet(this->instance->GetPosition(), this->color[this->tmpColorIndx]);
		}			

		this->instance->DrawPrimitive(AE_SOLID_PYRAMID);
		this->RenderBullet();
	}

	void OnClick() 
    {
		// Check for rayhit to the turret
		if(Raycast::CheckRayHit(*this->instance)) 
        {
			this->curRot = this->instance->GetAngle();

			// When left mouse button is clicked
			if(buttonIndx == 0) 
            {
				this->nextRot += 90;
				this->clickCount++;

				// When clickcount exceeds to 3 reset the counter
				if(this->clickCount > this->size - 1) 
                {
					this->clickCount = 0;
				}
			}

			// When right mouse button is clicked
			if(buttonIndx == 1) 
            {
				this->nextRot -= 90;
				this->clickCount--;

				// When clickcount is less than 0 set to the last color
				if(this->clickCount < 0) 
                {
					this->clickCount = this->size - 1;
				}
			}

			this->isMine = true;
		}

		// Do not update the rotation and color when I'm not in control 
		// return back to the caller
        if(!this->isMine &&
            (this->instance->GetAngle() == this->nextRot &&
           this->instance->GetColor() == this->color[this->clickCount]) * lifeColorOffset[this->life])
        {
            return;
        }

		if(this->buttonIndx == 0) 
        {
			if(this->curRot <= this->nextRot)
            {
				this->curRot += this->turnSpeed * 0.02f;
			}
			else 
            {
				this->instance->SetColor(this->color[this->clickCount] * lifeColorOffset[this->life]);
				this->tmpColorIndx = this->clickCount;
			}
		}

		if(this->buttonIndx == 1) 
        {
			if(this->curRot >= this->nextRot) 
            {
				this->curRot -= this->turnSpeed * 0.02f;
			}
			else 
            {
				this->instance->SetColor(this->color[this->clickCount] * lifeColorOffset[this->life]);
				this->tmpColorIndx = this->clickCount;
			}
		}

		this->instance->SetRotation(this->curRot, Vector3f::UP);
	}

	void SetControl(bool control) 
    {
		this->isMine = control;
	}

	void SetButtonClick(int button) 
    {
		this->buttonIndx = button;
	}

	void CheckCollisionWith(EnemySpawner* enemy) 
    {
		if(!enemy->enemyInstance.empty()) 
        {
			for(int i = 0; i < enemy->enemyInstance.size(); i++) 
            {
				if(enemy->enemyInstance[i]->instance->HasCollidedWith(*instance)) 
                {
					enemy->enemyInstance[i]->SubtractLife(3);
					enemy->enemyInstance[i]->EnemyExplode();
					enemy->SetSpawnDelay((float)RANDOM_VALUE);

                    if(this->life > 0)
                    {
                        life--;
                    }
                    else
                    {
                        this->isAlive = false;
                    }

					this->instance->SetColor(this->color[this->clickCount] * lifeColorOffset[this->life]);
				}
			}
		}

		if(!bullet.empty() && !enemy->enemyInstance.empty()) 
        {
			for(int j = 0; j < bullet.size(); j++) 
            {
				for(int i = 0; i < enemy->enemyInstance.size(); i++) 
                {
					if(enemy->enemyInstance[i]->instance->HasCollidedWith(*bullet[j])) 
                    {
						//if(enemy->enemyInstance[i]->GetLife() <= 0) {
						//	enemy->enemyInstance[i]->EnemyExplode();
						//}

						if(bullet[j]->GetColor() == enemy->enemyInstance[i]->instance->GetColor()) 
                        {
							enemy->enemyInstance[i]->SubtractLife(3);
							enemy->enemyInstance[i]->EnemyExplode();
							enemy->SetSpawnDelay((float)RANDOM_VALUE);

							multiplier = 2;
							score += multiplier;
						}
						else 
                        {
							enemy->enemyInstance[i]->SubtractLife(1);
							Color3 tmpColor = enemy->enemyInstance[i]->instance->GetColor();

							if(tmpColor == Color3::WHITE) 
                            {
								tmpColor = bullet[j]->GetColor() * 0.2f;
							}

							tmpColor += bullet[j]->GetColor() * 0.35f;
							enemy->enemyInstance[i]->instance->SetColor(tmpColor);

							multiplier = 1;
							
							if(enemy->enemyInstance[i]->GetLife() <= 0) 
                            {
								enemy->enemyInstance[i]->SubtractLife(3);
								enemy->enemyInstance[i]->EnemyExplode();
								enemy->SetSpawnDelay((float)RANDOM_VALUE);

								score += multiplier;
							}
						}

						RemoveBullet(j);
					}
				}
			}
		}

		for(int i = 0; i < enemy->enemyInstance.size(); i++) 
        {
			if(!enemy->enemyInstance[i]->GetAlive()) 
            {
				enemy->RemoveEnemy(i);
			}
		}
	}

	bool IsAlive() 
    {
		return this->isAlive;
	}

	GameObject* TurretInstance() 
    {
		return this->instance;
	}

private:
	int life;
	int clickCount;
	int buttonIndx;
	int tmpColorIndx;
	float curRot;
	float nextRot;
	float turnSpeed;
	bool isMine;
	bool isAlive;

	GameObject* instance;

protected:
};

Light* light = new Light();
Vector3f* rayDir = new Vector3f();
GameObject* tmpGo = new GameObject();

// Start Screen
Time* titleTime = new Time;
bool showTitle = true;

GameObject* addButton = new GameObject;
GameObject* subButton = new GameObject;

int optionIndx = 0;
char* options[3] = { " E a s y ", "M o d e r a t e", " H a r d " };
int turretCount[3] = { 1, 3, 5 };
float turretPosX[3] = { 0.0f, 1.0f, 2.0f };
float textPosX = 0.0f;

// Main Game
std::vector<Turret*> turret;
std::vector<EnemySpawner*> enemySpawner;

int wave = 1;
bool waveSpawned = false;
float curTime = 0.0f;
int additionalTime[3] = { 4, 5, 6 } ;
int timeCap[3] = { 10, 20, 30 };
//Time* waveTime = new Time;

// Credit Screen
Time* textSwitchTime = new Time;
int textIndx = 0;

void InitMainGame() 
{
	curTime = timeCap[optionIndx];
	for(int i = 0; i < turretCount[optionIndx]; i++) 
    {
		Turret* tmpTurret = new Turret;
		tmpTurret->TurretInstance()->SetPosition(Vector3f((i - turretPosX[optionIndx]) * 3.5f, -7.0f, 0.0f));
		tmpTurret->TurretInstance()->SetScale(Vector3f::ONE * 0.5f);
		tmpTurret->TurretInstance()->SetColliderSize(Vector3f::ONE * 3.0f);
		tmpTurret->TurretInstance()->SetActiveCollider(false);

		turret.push_back(tmpTurret);

		EnemySpawner* tmpSpawner = new EnemySpawner;
		tmpSpawner->SetSpawnerPosition(Vector3f((i - turretPosX[optionIndx]) * 3.5f, 8.0f, 0.0f));
		tmpSpawner->SetSpawnDelay((float)RANDOM_VALUE);
		enemySpawner.push_back(tmpSpawner);
	}
}

void Start() 
{
	light->SetPosition(Vector3f(0.0f, 0.0f, 10.0f));
	light->SetDiffuse(Color4(1.0f, 1.0f, 1.0f, 1.0f));

	// Start Screen
	addButton->SetPosition(Vector3f(1.5f, -1.0f, 0.0f));
	addButton->SetRotation(-90, Vector3f::FRONT);
	addButton->SetScale(Vector3f::ONE * 0.2f);
	addButton->SetActiveCollider(false);

	subButton->SetPosition(Vector3f(-1.5f, -1.0f, 0.0f));
	subButton->SetRotation(90, Vector3f::FRONT);
	subButton->SetScale(Vector3f::ONE * 0.2f);
	subButton->SetActiveCollider(false);

	rocket[0].InitializeObject("Assets\\rocket.obj");
}

void Update() 
{
	light->AddLight(AE_LIGHT1);
	Raycast::DrawRay(30, *rayDir);

    if(optionIndx == 2 && turret.size() > 3)
    {
        Raycast::CheckRayHit(*tmpGo);
    }

	if(gameMode == StartScreen) 
    {
		if(titleTime->LocalElapsedTime() > 1.0f) 
        {
			showTitle = !showTitle;
		}

        if(showTitle)
        {
            Text::AddText2D(-1.6f, 1.0f, "Space Shooter", FontSize::LARGE_FONT);
        }

		if(Raycast::CheckRayHit(*addButton)) 
        {
			optionIndx++;

            if(optionIndx > 2)
            {
                optionIndx = 0;
            }
		}

		if(Raycast::CheckRayHit(*subButton)) 
        {
			optionIndx--;

            if(optionIndx < 0)
            {
                optionIndx = 2;
            }
		}

		if(Input::GetKeyDown(' ')) 
        {
			InitMainGame();
			gameMode = MainGame;
		}

        if(optionIndx == 1)
        {
            textPosX = -1.1f;
        }
        else
        {
            textPosX = -0.6f;
        }

		Text::AddText2D(-0.9f, -0.5f, "Game Mode", FontSize::MEDIUM_FONT);
        Text::AddText2D(textPosX, -1.15f, options[optionIndx], FontSize::MEDIUM_FONT);
        Text::AddText2D(-1.7f, -2.5f, "Press spacebar to START!", FontSize::MEDIUM_FONT);

		addButton->DrawPrimitive(AE_SOLID_PYRAMID);
		subButton->DrawPrimitive(AE_SOLID_PYRAMID);
	}

	if(gameMode == MainGame) 
    {
		// Render Turrets
		if(!turret.empty()) 
        {
			if(turret.size() > 0) turret[0]->OnClick();
			if(turret.size() > 1) turret[1]->OnClick();
			if(turret.size() > 2) turret[2]->OnClick();
			if(turret.size() > 3) turret[3]->OnClick();
			if(turret.size() > 4) turret[4]->OnClick();

			for(int i = 0; i < turret.size(); i++) 
            {
				//if(turret.size() >= 4)
				//	turret[i]->TurretInstance()->SetColliderSize(Vector3f::One * 2.5);
				//else
				//	turret[i]->TurretInstance()->SetColliderSize(Vector3f::One);

				turret[i]->RenderTurret();

				turret[i]->CheckCollisionWith(enemySpawner[i]);							// NEW!

				//for(int j = 0; j < enemySpawner.size(); j++) {
				//	turret[i]->CheckCollisionWith(enemySpawner[j]);
				//}

				// When not alive, remove the turret
				if(!turret[i]->IsAlive()) 
                {
					enemySpawner.erase(enemySpawner.begin() + i);
					turret.erase(turret.begin() + i);
				}
			}
		}

		// Render Enemies
		if(!enemySpawner.empty()) 
        {
			for(int i = 0; i < enemySpawner.size(); i++) 
            {
				enemySpawner[i]->RenderEnemies();
				enemySpawner[i]->ShowTimer();
			}
		}

		if(!waveSpawned) 
        {
			if(!enemySpawner.empty()) 
            {
				if(enemySpawner.size() == 1)
                {
					enemySpawner[0]->SpawnEnemies();

					if(enemySpawner[0]->GetHasSpawned())
                    {
						waveSpawned = true;
					}
				}

				if(enemySpawner.size() == 2)
                {
					enemySpawner[0]->SpawnEnemies();
					enemySpawner[1]->SpawnEnemies();

					if(enemySpawner[0]->GetHasSpawned() &&
						enemySpawner[1]->GetHasSpawned()) 
                    {
						waveSpawned = true;
					}
				}

				if(enemySpawner.size() == 3) 
                {
					enemySpawner[0]->SpawnEnemies();
					enemySpawner[1]->SpawnEnemies();
					enemySpawner[2]->SpawnEnemies();

					if(enemySpawner[0]->GetHasSpawned() &&
						enemySpawner[1]->GetHasSpawned() &&
						enemySpawner[2]->GetHasSpawned()) 
                    {
						waveSpawned = true;
					}
				}

				if(enemySpawner.size() == 4)
                {
					enemySpawner[0]->SpawnEnemies();
					enemySpawner[1]->SpawnEnemies();
					enemySpawner[2]->SpawnEnemies();
					enemySpawner[3]->SpawnEnemies();

					if(enemySpawner[0]->GetHasSpawned() &&
						enemySpawner[1]->GetHasSpawned() &&
						enemySpawner[2]->GetHasSpawned() &&
						enemySpawner[3]->GetHasSpawned())
                    {
						waveSpawned = true;
					}
				}

				if(enemySpawner.size() == 5) 
                {
					enemySpawner[0]->SpawnEnemies();
					enemySpawner[1]->SpawnEnemies();
					enemySpawner[2]->SpawnEnemies();
					enemySpawner[3]->SpawnEnemies();
					enemySpawner[4]->SpawnEnemies();

					if(enemySpawner[0]->GetHasSpawned() &&
						enemySpawner[1]->GetHasSpawned() &&
						enemySpawner[2]->GetHasSpawned() &&
						enemySpawner[3]->GetHasSpawned() &&
						enemySpawner[4]->GetHasSpawned())
                    {
						waveSpawned = true;
					}
				}

				//for(int i = 0; i < enemySpawner.size(); i++) {
				//	enemySpawner[i]->SpawnEnemies();

				//	if(!enemySpawner[i]->enemyInstance.empty()) {
				//		waveSpawned = true;
				//	}
				//}
			}
		}
		else 
        {
			if(!enemySpawner.empty())
            {
				if(enemySpawner.size() == 1) 
                {
					if(enemySpawner[0]->enemyInstance.empty())
                    {

						if(enemySpawner[0]->GetHasSpawned())
                        {
							wave++;

							curTime += additionalTime[optionIndx];

                            if(curTime > timeCap[optionIndx])
                            {
                                curTime = timeCap[optionIndx];
                            }

							enemySpawner[0]->SetHasSpawned(false);
						}

						waveSpawned = false;
					}
				}

				if(enemySpawner.size() == 2) 
                {
					if(enemySpawner[0]->enemyInstance.empty() &&
						enemySpawner[1]->enemyInstance.empty()) 
                    {

						if(enemySpawner[0]->GetHasSpawned() && enemySpawner[1]->GetHasSpawned())
                        {
							wave++;

							curTime += additionalTime[optionIndx];

                            if(curTime > timeCap[optionIndx])
                            {
                                curTime = timeCap[optionIndx];
                            }

							enemySpawner[0]->SetHasSpawned(false);
							enemySpawner[1]->SetHasSpawned(false);
						}

						waveSpawned = false;
					}
				}

				if(enemySpawner.size() == 3) 
                {
					if(enemySpawner[0]->enemyInstance.empty() &&
						enemySpawner[1]->enemyInstance.empty() &&
						enemySpawner[2]->enemyInstance.empty()) 
                    {

						if(enemySpawner[0]->GetHasSpawned() && enemySpawner[1]->GetHasSpawned() &&
							enemySpawner[2]->GetHasSpawned()) 
                        {
							wave++;

							
							curTime += additionalTime[optionIndx];

                            if(curTime > timeCap[optionIndx])
                            {
                                curTime = timeCap[optionIndx];
                            }

							enemySpawner[0]->SetHasSpawned(false);
							enemySpawner[1]->SetHasSpawned(false);
							enemySpawner[2]->SetHasSpawned(false);
						}

						waveSpawned = false;
					}
				}

				if(enemySpawner.size() == 4)
                {
					if(enemySpawner[0]->enemyInstance.empty() && 
						enemySpawner[1]->enemyInstance.empty() &&
						enemySpawner[2]->enemyInstance.empty() &&
						enemySpawner[3]->enemyInstance.empty())
                    {

						if(enemySpawner[0]->GetHasSpawned() && enemySpawner[1]->GetHasSpawned() &&
							enemySpawner[2]->GetHasSpawned() && enemySpawner[3]->GetHasSpawned())
                        {
							wave++;

							curTime += additionalTime[optionIndx];

                            if(curTime > timeCap[optionIndx])
                            {
                                curTime = timeCap[optionIndx];
                            }

							enemySpawner[0]->SetHasSpawned(false);
							enemySpawner[1]->SetHasSpawned(false);
							enemySpawner[2]->SetHasSpawned(false);
							enemySpawner[3]->SetHasSpawned(false);
						}

						waveSpawned = false;
					}
				}

				if(enemySpawner.size() == 5) 
                {
					if(enemySpawner[0]->enemyInstance.empty() &&
						enemySpawner[1]->enemyInstance.empty() &&
						enemySpawner[2]->enemyInstance.empty() &&
						enemySpawner[3]->enemyInstance.empty() &&
						enemySpawner[4]->enemyInstance.empty())
                    {

						if(enemySpawner[0]->GetHasSpawned() && enemySpawner[1]->GetHasSpawned() &&
							enemySpawner[2]->GetHasSpawned() && enemySpawner[3]->GetHasSpawned() &&
							enemySpawner[4]->GetHasSpawned()) 
                        {
							wave++;

							curTime += additionalTime[optionIndx];

                            if(curTime > timeCap[optionIndx])
                            {
                                curTime = timeCap[optionIndx];
                            }

							enemySpawner[0]->SetHasSpawned(false);
							enemySpawner[1]->SetHasSpawned(false);
							enemySpawner[2]->SetHasSpawned(false);
							enemySpawner[3]->SetHasSpawned(false);
							enemySpawner[4]->SetHasSpawned(false);
						}

						waveSpawned = false;
					}
				}
			}
		}

		if(turret.empty() || curTime <= 0.0f) 
        {
			gameMode = CreditScreen;
		}

		char tmpText[100];
		curTime -= 0.01f;
		sprintf(tmpText, "Time Remaining: %.1fs", curTime);
        Text::AddText3D(-10.0f, 7.0f, 1.0f, tmpText, FontSize::MEDIUM_FONT);

		sprintf(tmpText, "Wave %i", wave);
		Text::AddText3D(-0.5f, 7.0f, 1.0f, tmpText, FontSize::MEDIUM_FONT);

		sprintf(tmpText, "Score %i", score);
        Text::AddText3D(8.0f, 7.0f, 1.0f, tmpText, FontSize::MEDIUM_FONT);
	}
	
	if(gameMode == CreditScreen) 
    {
		if(titleTime->LocalElapsedTime() > 1.0f) 
        {
			showTitle = !showTitle;
		}

        if(showTitle)
        {
            Text::AddText2D(-1.6f, 1.0f, "Space Shooter", FontSize::LARGE_FONT);
        }

		float time = textSwitchTime->LocalElapsedTime();

		if(time > 2.0f) 
        {
			textIndx++;

            if(textIndx > 3)
            {
                textIndx = 0;
            }

			textSwitchTime->LocalReset();
		}

		char tmpText[100];

        if(textIndx == 0)
        {

            Text::AddText2D(-0.95f, -0.5f, "GAME OVER!", FontSize::MEDIUM_FONT);
        }

		if(textIndx == 1) 
        {
			sprintf(tmpText, "Final Score: %i", score);
            Text::AddText2D(-0.95f, -0.5f, tmpText, FontSize::MEDIUM_FONT);

			sprintf(tmpText, "Maximum Waves: %i", wave);
            Text::AddText2D(-1.35f, -1.0f, tmpText, FontSize::MEDIUM_FONT);
		}

		if(textIndx == 2) 
        {
            Text::AddText2D(-2.0f, -0.5f, "Created by: Anthony Ganzon", FontSize::MEDIUM_FONT);
            Text::AddText2D(-0.9f, -1.0f, "PROJECT K3AI", FontSize::MEDIUM_FONT);
		}

		if(textIndx == 3) 
        {
            Text::AddText2D(-1.5f, -0.5f, "Thank you for playing!", FontSize::MEDIUM_FONT);
            Text::AddText2D(-1.0f, -1.0f, "Press Esc to Exit", FontSize::MEDIUM_FONT);
		}
	}
    else
    {
        textSwitchTime->LocalReset();
    }
}

void MouseDown(int x, int y) 
{
	//if(Input::GetMouseDown(MouseType::Left)) 
 //   {
	//	for(int i = 0; i < turret.size(); i++)
 //       {
	//		turret[i]->SetControl(false);
	//		turret[i]->SetButtonClick(0);
	//	}
	//}

	//if(Input::GetMouseDown(MouseType::Right)) 
 //   {
	//	for(int i = 0; i < turret.size(); i++) 
 //       {
	//		turret[i]->SetControl(false);
	//		turret[i]->SetButtonClick(1);
	//	}
	//}
}

int main(int argc, char** argv) 
{
	atomStartFunc(&Start);
	atomUpdateFunc(&Update);

	//atomMouseDownFunc(&MouseDown);
	atomCameraPosition(0.0f, 0.0f, 20.0f);

	atomInitialize(argc, argv);
	return 0;
}