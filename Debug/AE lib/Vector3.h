#ifndef __ATOMENGINE_VECTOR3_LIBRARY_H__
# define __ATOMENGINE_VECTOR3_LIBRARY_H__

/* definition for math library */
# ifndef __ATOMENGINE_MATH_LIBRARY_H__
#  include "Math.h"
# endif

/*
	A macro defined to export or import functions, variables, etc.
*/
# ifdef ATOMAPI
#  define ATOMAPI __declspec(dllexport)
# else
#  define ATOMAPI __declspec(dllimport)
# endif

namespace Vector3Library {
	using namespace MathLibrary;

	/* class that holds the vector3 library and its functionalities */
	class ATOMAPI Vector3 {
	public:
		Vector3();
		Vector3(float x, float y, float z);
		~Vector3();

		Vector3 &operator=(const Vector3 &rhs);
		Vector3 &operator-() const;

		Vector3 &operator+=(const Vector3 &rhs);
		Vector3 operator+(const Vector3 &op);

		Vector3 &operator-=(const Vector3 &rhs);
		Vector3 operator-(const Vector3 &op);

		Vector3 &operator*=(const float scalar);
		Vector3 operator*(const float scalar);

		Vector3 &operator*=(const Vector3 &rhs);
		Vector3 operator*(const Vector3 &op);

		Vector3 &operator/=(const float scalar);
		Vector3 operator/(const float scalar);

		Vector3 &operator/=(const Vector3 &rhs);
		Vector3 operator/(const Vector3 &op);

		bool operator==(const Vector3 &other);
		bool operator!=(const Vector3 &other);

		bool operator>(const Vector3 &other);
		bool operator>=(const Vector3 &other);

		bool operator<(const Vector3 &other);
		bool operator<=(const Vector3 &other);

		float Length();
		Vector3 &Normalize();
		float Dot(const Vector3& vec1, const Vector3& vec2);
		Vector3 Cross(const Vector3& vec1, const Vector3& vec2);
		void Print();

		static Vector3 Zero;	static Vector3 Front;
		static Vector3 One;		static Vector3 Back;
		static Vector3 Up;		static Vector3 Right;
		static Vector3 Down;	static Vector3 Left;

		float X;
		float Y;
		float Z;
	private:
	protected:
	};
}

#endif