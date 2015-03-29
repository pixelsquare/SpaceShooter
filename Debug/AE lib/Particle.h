#ifndef __ATOMENGINE_PARTICLE_LIBRARY_H__
# define __ATOMENGINE_PARTICLE_LIBRARY_H__

/* definition for physics library */
# ifndef __ATOMENGINE_PHYSICS_LIBRARY_H__
#  include "Physics.h"
# endif

/* definition for time library */
# ifndef __ATOMENGINE_TIME_LIBRARY_H__
#  include "Time.h"
# endif

/*
	A macro defined to export or import functions, variables, etc.
*/
# ifdef ATOMAPI
#  define ATOMAPI __declspec(dllexport)
# else
#  define ATOMAPI __declspec(dllimport)
# endif

/*
	Particle subsystem uses Vertex Buffer Objects (VBO)
	it is made from points to create a particle effect.
	It uses linked list to render all the particles over time.


	credits to: Rob Bateman
*/
namespace ParticleLibrary {
	using namespace PhysicsLibrary;
	using namespace TimeLibrary;

	/* class that holds particle subsystem */
	class ATOMAPI Particle : public Physics {
	public:
		Particle();
		~Particle();

		void SetActiveParticle(bool active);
		void SetAutoDestruct(bool active);

		void SetEnergy(int min, int max);
		void SetEmission(int min, int max);

		void SetEllipsoid(Vector3 ellipsoid);
		void SetEllipsoid(float x, float y, float z);

		void SetRandomVelocity(Vector3 randomVel);
		void SetRandomVelocity(float x, float y, float z);

		void SetColors(Color3* color, size_t size);
		void EmitParticles();

		long GetParticleCount();
		bool GetActiveParticle();
		bool GetIsDestroyed();

	private:
		Particle(Vector3 pos, Vector3 oppositePos, Vector3 vel,
			Vector3 randomVel, Color3 col, Vector3 norm, int minLife, int maxLife);

		void UpdateParticles(float dt);

		bool autoDestruct;
		bool isDestroyed;
		Time* particleTime;
		float destructTime;

		int minEnergy;
		int maxEnergy;
		float life;
		bool isActive;
		int particleCount;

		long curParticleCount;

		Vector3 particlePos;
		Vector3 randomVelocity;
		Vector3 ellipsoid;
		Vector3 normal;

		Color3* colors;
		unsigned int colorSize;

		Particle* start;
		Particle* end;
		Particle* last;
	protected:
		bool IsInsideSphere(Vector3 center, double radius, Vector3 pos);
	};
}

#endif