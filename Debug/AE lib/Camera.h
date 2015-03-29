#ifndef __ATOMENGINE_CAMERA_LIBRARY_H__
# define __ATOMENGINE_CAMERA_LIBRARY_H__

/* definition for Transformation library */
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

namespace CameraLibrary { 
	using namespace TransformationLibrary;

	/* Window Properties */
	struct Window {
		Window() {
			this->windowHandle = 0;
			this->width = 800;
			this->height = 600;
			this->name = "Atom Engine v2.0 Project";
			this->color = Color4(0.0f, 0.0f, 0.0f, 1.0f);
		}

		int windowHandle;
		char *name;
		int width;
		int height;
		Color4 color;

	}; extern Window atomWindow;

	/* Camera Properties */
	struct Camera {
		Camera() {
			this->Position = Vector3(0.0f, 0.0f, 10.0f);
			this->LookAt = Vector3(0.0f, 0.0f, 0.0f);
			this->Up = Vector3(0.0f, 1.0f, 0.0f);
		}

		Vector3 Position;
		Vector3 LookAt;
		Vector3 Up;

	}; extern Camera atomCamera;

	/* Atom Engine edit mode properties */
	struct CameraEditMode {
		CameraEditMode() {
			this->position = Vector3(0.01f, 0.01f, 10.0f);
			this->rotation = Vector3(0.01f, 0.01f, 0.0f);
			this->lastX = 0;
			this->lastY = 0;
			this->mouseClick[0] = false;
			this->mouseClick[1] = false;
			this->mouseClick[2] = false;
		}

		Vector3 position;
		Vector3 rotation;
		int lastX;
		int lastY;
		bool mouseClick[3];

	}; extern CameraEditMode editMode;

	extern bool inEditMode;

	/* Functions that exported and can be used outside  */
	extern void ATOMAPI atomCameraPosition(Vector3 position);
	extern void ATOMAPI atomCameraPosition(float x, float y, float z);
	
	extern void ATOMAPI atomCameraLookAt(Vector3 lookAt);
	extern void ATOMAPI atomCameraLookAt(float x, float y, float z);

	extern void ATOMAPI atomCameraUp(Vector3 up);
	extern void ATOMAPI atomCameraUp(float x, float y, float z);

	extern void ATOMAPI atomEditMode(bool flag);
}

#endif