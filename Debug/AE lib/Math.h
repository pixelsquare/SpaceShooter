#ifndef __ATOMENGINE_MATH_LIBRARY_H__
# define __ATOMENGINE_MATH_LIBRARY_H__

/* 	Math library is the root library of the atom engine. */

/*
	A macro defined to export or import functions, variables, etc.
*/

#  define ATOMAPI __declspec(dllexport)
#include <Math.h>

/* 
	all the functions are in static to be used  outside
	also it doesn't need an instance. it is declared in
	the atom header.
*/
namespace MathLibrary { 
	class Math {
	public:
		static float Sqrtf(float value);
		static float PI();

		static double Abs(double value);
		static double Sin(double value);
		static double Cos(double value);
		static double Tan(double value);

		static double Asin(double value);
		static double Acos(double value);
		static double Atan(double value);

		static double Exp(double value);
		static double Log(double value);
		static double Pow(double val1, double val2);

		static double Ceil(double value);
		static double Floor(double value);
		static double Round(double value, double placeValue);
	private:
	protected:
	};
}

#endif