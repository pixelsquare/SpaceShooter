#ifndef __ATOMENGINE_COLLISION_LIBRARY_H__
# define __ATOMENGINE_COLLISION_LIBRARY_H__

/* definition for transformation library */
# ifndef __ATOMENGINE_TRANSFORMATION_LIBRARY_H__
#  include "Transformation.h"
# endif

/*
	A macro defined to export or import functions, variables, etc.
*/
# ifdef ATOMAPI
#  define ATOMAPI __declspec(dllexport)
# else
#  define ATOMAPI __declspec(dllimport)
# endif

namespace CollisionLibrary {
	using namespace TransformationLibrary;

	/* Options for the collider type */
	enum ColliderType {
		None, Cube, Sphere
	};

	/* Class that holds the collision detection subsystem */
	class ATOMAPI Collision : public Transformation {
	public:
		Collision();
		~Collision();

		void SetActiveCollider(bool active);			// Active Collider Box
		void SetActiveCollision(bool active);			// Active Collision Detection
		void SetColliderType(ColliderType type);

		void SetColliderRadius(float rad);
		void SetColliderSize(Vector3 size);
		void SetColliderSize(float x, float y, float z);

		bool HasCollidedWith(Collision &object);

		Vector3 colliderOffset;

	private:
		Vector3* cubeVertices;
		Color3* cubeColor;

		bool isActive;
		bool applyCollision;
		float radius;
		float minDistance;
		float distance;
		Vector3 relativePos;

		int drawingType;
		long connectedPts;
		bool initCollider;
	protected:
		void DrawCollider();
		void RescaleCube(Vector3 scl);
		void RescaleSphere(float rad);

		ColliderType colliderType;

	};
}

#endif