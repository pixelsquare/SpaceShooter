#ifndef __ATOMENGINE_PHYSICS_LIBRARY_H__
# define __ATOMENGINE_PHYSICS_LIBRARY_H__

/* definition for collision library */
# ifndef __ATOMENGINE_COLLISION_LIBRARY_H__
#  include "Collision.h"
# endif

/*
	A macro defined to export or import functions, variables, etc.
*/
# ifdef ATOMAPI
#  define ATOMAPI __declspec(dllexport)
# else
#  define ATOMAPI __declspec(dllimport)
# endif

/* macro for gravity */
#define GRAVITY 9.8f

namespace PhysicsLibrary {
	using namespace CollisionLibrary;

	/* class that holds the physics subsystem */
	class ATOMAPI Physics : public Collision { 
	public:
		Physics();
		~Physics();

		void SetActivePhysics(bool active);
		void SetMass(float objectMass);

		void AddVelocity(Vector3 objVel);
		void AddVelocity(float x, float y, float z);

		void SetVelocity(Vector3 velocity);
		void SetVelocity(float x, float y, float z);
		Vector3 GetVelocity();

		void AddAcceleration(Vector3 objAccel);
		void AddAcceleration(float x, float y, float z);

		void SetAcceleration(Vector3 acceleration);
		void SetAcceleration(float x, float y, float z);
		Vector3 GetAcceleration();

		void UseGravity(bool flag);

	private:
		bool useGravity;
		bool gravityApplied;
		bool isActive;

	protected:
		float mass;

		Vector3 velocity;
		Vector3 acceleration;

		void ApplyPhysics();

	};
};

#endif