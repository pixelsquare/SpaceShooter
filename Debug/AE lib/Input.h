#ifndef __ATOMENGINE_INPUT_LIBRARY_H__
# define __ATOMENGINE_INPUT_LIBRARY_H__

/* definition for raycast library */
# ifndef __ATOMENGINE_RAYCAST_LIBRARY_H__
#  include "AE lib\Raycast.h"
# endif

/*
	A macro defined to export or import functions, variables, etc.
*/
# ifdef ATOMAPI
#  define ATOMAPI __declspec(dllexport)
# else
#  define ATOMAPI __declspec(dllimport)
# endif

namespace InputLibrary {
	using namespace RaycastLibrary;

	extern bool keyDown[256];
	extern unsigned char inputKey;
	extern bool isPressed;

	extern bool specialKeyHold[21];
	extern int inputSpecialKey;
	extern bool specialPressed;

	/* Atom engine pre-made special keys */
	enum ATOMAPI SpecialKey {
		AE_F1 = 1 , AE_F2 = 2, AE_F3 = 3, AE_F4 = 4, AE_F5 = 5, AE_F6 = 6,
		AE_F7 = 7, AE_F8 = 8, AE_F9 = 9, AE_F10 = 10, AE_F11 = 11, AE_F12 = 12,
		AE_LEFT = 100, AE_UP = 101, AE_RIGHT = 102, AE_DOWN = 103, AE_PAGEUP = 104,
		AE_PAGEDOWN = 105, AE_HOME = 106, AE_END = 107, AE_INSERT = 108

	};

	extern bool ATOMAPI GetKey(unsigned char key);
	extern bool ATOMAPI GetSpecialKey(SpecialKey type);
	extern bool ATOMAPI GetKeyDown(unsigned char key);

	/* Private functions */
	extern void atomOnKeyDown(unsigned char key, int x, int y);
	extern void atomOnKeyHold(unsigned char key, int x, int y);
	extern void atomOnSpecialKey(int key, int x, int y);
	extern void atomOnMouseButton(int button, int state, int x, int y);
	extern void atomOnMouseMove(int x, int y);
	extern void atomOnPassiveMouse(int x, int y);

	extern void ATOMAPI atomMouseFunc( void(*func)(int x, int y) );
	extern void ATOMAPI atomMouseDownFunc( void(*func)(int x, int y) );
	extern void ATOMAPI atomPassiveMouseFunc( void(*func)(int x, int y) );

	/* Options for mouse clicking */
	enum ATOMAPI MouseType {
		Left = 0,
		Middle = 1,
		Right = 2
	};

	extern bool ATOMAPI GetMouseDown(MouseType type);
}

#endif