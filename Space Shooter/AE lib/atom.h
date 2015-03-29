#ifndef __ATOM_ENGINE_V2_H__
#define __ATOM_ENGINE_V2_H__

/* Copyright (c) Anthony M. Ganzon, 2013 */

/*
	Atom Engine is freely distributable without licensing fees.
	The engine uses glut to render its assets and other graphic
	related stuff. It is made by group college students at their
	3rd year, taking up game design and development. This is made 
	for a game engine course at De la salle-College of Saint Benilde.
*/

/*
	Library or subsystem definition
*/

# ifndef __ATOMENGINE_GAMEOBJECT_LIBRARY_H__
#  include "GameObject.h"
# endif

# ifndef __ATOMENGINE_PARTICLE_LIBRARY_H__
#  include "Particle.h"
# endif

# ifndef __ATOMENGINE_TEXT_LIBRARY_H__
#  include "Text.h"
# endif

# ifndef __ATOMENGINE_INPUT_LIBRARY_H__
#  include "Input.h"
# endif

# ifndef __ATOMENGINE_SOUND_LIBRARY_H__
#  include "Sound.h"
# endif

# ifndef __ATOM_ENGINE_LIGHT_LIBRARY_H__
#  include "Light.h"
# endif

/*
	GLUT 3.7 now tries to avoid including <windows.h>
	to avoid name space pollution.
*/

# if defined (_WIN32)
#  define WIN32_LEAN_AND_MEAN
#   include <Windows.h>
#	include <time.h>

/*
	A macro defined to export or import functions, variables, etc.
*/

#   ifdef ATOMAPI
#    define ATOM_ATOMAPI_DEFINED
#    define ATOMAPI __declspec(dllexport)
#   else
#    define ATOMAPI __declspec(dllimport)
#   endif

# endif

#pragma comment (lib, "atom.lib")	/* link with atom lib */

#include <glut.h>
#include <vector>

/* define ATOMAPI to null if we are not on win32 */

#if !defined (_WIN32)
# define ATOMAPI
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* generic data types defined in atom engine manner */
typedef unsigned int AEenum;
typedef unsigned char AEboolean;
typedef signed char AEbyte;
typedef short AEshort;
typedef int AEint;
typedef int AEsizei;
typedef float AEfloat;
typedef float AEclampf;
typedef double AEdouble;
typedef double AEclampd;
typedef void AEvoid;

/* macros used in rendering / loading primitives */
#define AE_SOLID_CUBE		0x32	//"Assets\\Cube.obj"
#define AE_SOLID_PLANE		0x33	//"Assets\\Plane.obj"
#define AE_SOLID_SPHERE		0x34	//"Assets\\Sphere.obj"
#define AE_SOLID_CAPSULE	0x35	//"Assets\\Capsule.obj"
#define AE_SOLID_CONE		0x36	//"Assets\\Cone.obj"
#define AE_SOLID_CYLINDER	0x37	//"Assets\\Cylinder.obj"
#define AE_SOLID_PYRAMID	0x38	//"Assets\\Pyramid.obj"
#define AE_SOLID_TORUS		0x39	//"Assets\\Torus.obj"

#define AE_LIGHT1	0x41
#define AE_LIGHT2	0x42
#define AE_LIGHT3	0x43
#define AE_LIGHT4	0x44
#define AE_LIGHT5	0x45
#define AE_LIGHT6	0x46
#define AE_LIGHT7	0x47
#define AE_LIGHT8	0x48

#ifndef ATOM_API_VERSION		/* allow this to be overriden */
#define ATOM_API_VERSION	1	/* atom engine api version */
#endif

# if (ATOM_API_VERSION >= 1)

namespace AtomEngine {
	/* subsystem namespace definition */
	using namespace GameObjectLibrary;
	using namespace ParticleLibrary;
	using namespace TextLibrary;
	using namespace InputLibrary;
	using namespace SoundLibrary;
	using namespace LightLibrary;

	/* important functions to be declared in main */
	extern void ATOMAPI atomStartFunc( void(*func)(void) );
	extern void ATOMAPI atomUpdateFunc( void(*func)(void) );
	extern void ATOMAPI atomInitialize(int argc, char **argv);

	/* additional window settings for atom engine window */
	extern void ATOMAPI atomWindowWidth(int width);
	extern void ATOMAPI atomWindowHeight(int height);
	extern void ATOMAPI atomWindowName(char *name);
	extern void ATOMAPI atomWindowBGColor(double r, double g, double b, double a);
}

/* static funtions in math library */
namespace MathLibrary {
	float Math::Sqrtf(float value) {
		return sqrtf(value);
	}

	float Math::PI() {
		return 3.14159265359f;
	}

	double Math::Abs(double value) {
		return abs(value);
	}

	double Math::Sin(double value) {
		return sin(value);
	}

	double Math::Cos(double value) {
		return cos(value);
	}

	double Math::Asin(double value) {
		return asin(value);
	}

	double Math::Acos(double value) {
		return acos(value);
	}

	double Math::Atan(double value) {
		return atan(value);
	}

	double Math::Exp(double value) {
		return exp(value);
	}

	double Math::Log(double value) {
		return log(value);
	}

	double Math::Pow(double val1, double val2) {
		return pow(val1, val2);
	}

	double Math::Ceil(double value) {
		return ceil(value);
	}

	double Math::Floor(double value) {
		return floor(value);
	}

	double Math::Round(double value, double placeValue) {
		return Math::Floor(value * placeValue + 0.5f) / placeValue;
	}
}

/* static variable shortcuts for vector3 library */
namespace Vector3Library {
	Vector3 Vector3::Zero	= Vector3(0.0f, 0.0f, 0.0f);
	Vector3 Vector3::One	= Vector3(1.0f, 1.0f, 1.0f);
	Vector3 Vector3::Up		= Vector3(0.0f, 1.0f, 0.0f);
	Vector3 Vector3::Down	= Vector3(0.0f, -1.0f, 0.0f);
	Vector3 Vector3::Front	= Vector3(0.0f, 0.0f, 1.0f);
	Vector3 Vector3::Back	= Vector3(0.0f, 0.0f, -1.0f);
	Vector3 Vector3::Right	= Vector3(1.0f, 0.0f, 0.0f);
	Vector3 Vector3::Left	= Vector3(-1.0f, 0.0f, 0.0f);
}

/* static variable shortcuts for color3 library */
namespace TransformationLibrary {
	Color3 Color3::Red		= Color3(1.0f, 0.0f, 0.0f);
	Color3 Color3::Green	= Color3(0.0f, 1.0f, 0.0f);
	Color3 Color3::Blue		= Color3(0.0f, 0.0f, 1.0f);
	Color3 Color3::White	= Color3(1.0f, 1.0f, 1.0f);
	Color3 Color3::Yellow	= Color3(1.0f, 1.0f, 0.0f);
	Color3 Color3::Cyan		= Color3(0.0f, 1.0f, 1.0f);
	Color3 Color3::Magenta	= Color3(1.0f, 0.0f, 1.0f);
	Color3 Color3::Gray		= Color3(0.5f, 0.5f, 0.5f);

	Color4 Color4::Red		= Color4(1.0f, 0.0f, 0.0f, 1.0f);
	Color4 Color4::Green	= Color4(0.0f, 1.0f, 0.0f, 1.0f);
	Color4 Color4::Blue		= Color4(0.0f, 0.0f, 1.0f, 1.0f);
	Color4 Color4::White	= Color4(1.0f, 1.0f, 1.0f, 1.0f);
	Color4 Color4::Yellow	= Color4(1.0f, 1.0f, 0.0f, 1.0f);
	Color4 Color4::Cyan		= Color4(0.0f, 1.0f, 1.0f, 1.0f);
	Color4 Color4::Magenta	= Color4(1.0f, 0.0f, 1.0f, 1.0f);
	Color4 Color4::Gray		= Color4(0.5f, 0.5f, 0.5f, 1.0f);
}

/* 
	atom engine uses windows.h audio library .
	sound library static functions were made
	since the audio library can play single sound
	per instance.
*/
namespace SoundLibrary {
	Sound* sound = new Sound;
	void Sound::Play(LPCTSTR name) {
		if(!sound->muteSound) {
			if(sound->loopSound)
				PlaySound(name, NULL, SND_ASYNC|SND_FILENAME|SND_LOOP);
			else
				PlaySound(name, NULL, SND_ASYNC|SND_FILENAME);
		}
	}

	void Sound::Stop() {
		PlaySound(NULL, 0, 0);
	}

	void Sound::Loop(bool loop) {
		sound->loopSound = loop;
	}

	void Sound::Mute(bool mute) {
		sound->muteSound = mute;
	}
}

namespace TimeLibrary {
	Time *gameTime = new Time;
	float Time::GetFPS() {
		return 1.0f / gameTime->LocalDeltaTime();
	}

	float Time::GetDeltaTime() {
		return gameTime->LocalDeltaTime();
	}

	float Time::GetElapsedTime() {
		return gameTime->LocalElapsedTime();
	}

	void Time::Reset() {
		gameTime->LocalReset();
	}
}


# endif

#ifdef __cplusplus
}
#endif

#endif