#ifndef __ATOMENGINE_RAYCAST_LIBRARY_H__
# define __ATOMENGINE_RAYCAST_LIBRARY_H__

/* definition for gameobject library */
# ifndef __ATOMENGINE_GAMEOBJECT_LIBRARY_H__
#  include "GameObject.h"
# endif

/* definition for camera library */
# ifndef __ATOMENGINE_CAMERA_LIBRARY_H__
#  include "Camera.h"
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
	Raycast subsystem 
	credits to: Mr. Ryan Baclit (professor)
*/
namespace RaycastLibrary {
	using namespace GameObjectLibrary;
	using namespace CameraLibrary;

	void RayPick(float x, float y);
	void ATOMAPI DrawRay(int length, Vector3 &vec);
	bool ATOMAPI CheckRayHit(GameObject &object);
}

#endif