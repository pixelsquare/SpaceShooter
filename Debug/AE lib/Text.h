#ifndef __ATOMENGINE_TEXT_LIBRARY_H__
# define __ATOMENGINE_TEXT_LIBRARY_H__

/*
	A macro defined to export or import functions, variables, etc.
*/
# ifdef ATOMAPI
#  define ATOMAPI __declspec(dllexport)
# else
#  define ATOMAPI __declspec(dllimport)
# endif

/* 2D and 3D texts */
namespace TextLibrary {
	/* sizes for the text */
	enum ATOMAPI FontSize {
		SMALL_FONT,
		MEDIUM_FONT,
		LARGE_FONT
	};

	extern void ATOMAPI AddText2D(float x, float y, char* string, FontSize type);
	extern void ATOMAPI AddText3D(float x, float y, float z, char* string, FontSize type);
}

#endif