#ifndef __ATOMENGINE_SOUND_LIBRARY_H__
#define __ATOMENGINE_SOUND_LIBRARY_H__

/*
	A macro defined to export or import functions, variables, etc.
*/
# ifdef ATOMAPI
#  define ATOMAPI __declspec(dllexport)
# else
#  define ATOMAPI __declspec(dllimport)
# endif

#include <Windows.h>
#include <MMSystem.h>

/* 
	Sound library uses static functions since it 
	uses a single instance. all static functions are
	declared in the atom header.
*/

namespace SoundLibrary {
	/* class that holds the sound subsystem */
	class ATOMAPI Sound {
	public:
		Sound();

		static void Play(LPCTSTR name);
		static void Stop();
		static void Loop(bool loop);
		static void Mute(bool mute);
	private:
		bool muteSound;
		bool loopSound;
	protected:

	};
}

#endif