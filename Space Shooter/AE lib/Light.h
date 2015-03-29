#ifndef __ATOM_ENGINE_LIGHT_LIBRARY_H__
#define __ATOM_ENGINE_LIGHT_LIBRARY_H__

/* Light must be defined in the main project */

/* definition for Transformation library */
# ifndef __ATOMENGINE_TRANSFORMATION_LIBRARY_H__
#  include "Transformation.h"
# endif

#include <glut.h>

/*
	A macro defined to export or import functions, variables, etc.
*/
# ifdef ATOMAPI
#  define ATOMAPI __declspec(dllexport)
# else
#  define ATOMAPI __declspec(dllimport)
# endif

namespace LightLibrary {
	using namespace TransformationLibrary;

	/* class that holds the lighting subsystem */
	class ATOMAPI Lighting {
	public:
		Lighting();

		void AddLight(int lightType);

		void SetActiveLight(bool active);

		void SetPosition(Vector3 position);
		void SetPosition(float x, float y, float z);

		void SetAmbient(Color4 ambient);
		void SetAmbient(float r, float g, float b, float a);

		void SetDiffuse(Color4 diffuse);
		void SetDiffuse(float r, float g, float b, float a);

		void SetSpecular(Color4 specular);
		void SetSpecular(float r, float g, float b, float a);

	private:
		Vector3 position;
		Color4 ambient;
		Color4 diffuse;
		Color4 specular;
		bool isActive;
	protected:
	};
}

#endif