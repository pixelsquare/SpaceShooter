#ifndef __ATOMENGINE_TRANSFORMATION_LIBRARY_H__
# define __ATOMENGINE_TRANSFORMATION_LIBRARY_H__

/* definition for vector3 library */
# ifndef __ATOMENGINE_VECTOR3_LIBRARY_H__
#  include "Vector3.h"
# endif

/* definition for time library */
# ifndef __ATOMENGINE_TIME_LIBRARY_H__
#  include "Time.h"
# endif

/*
	A macro defined to export or import functions, variables, etc.
*/
# ifdef ATOMAPI
#  define ATOMAPI __declspec(dllexport)
# else
#  define ATOMAPI __declspec(dllimport)
# endif

namespace TransformationLibrary {
	using namespace Vector3Library;
	using namespace TimeLibrary;

	/* class that holds the colors that can be used outside */
	class ATOMAPI Color3 {
	public:
		Color3();
		Color3(float red, float green, float blue);
		~Color3();

		Color3 &operator=(const Color3 &rhs);

		Color3 &operator+=(const Color3 &rhs);
		Color3 operator+(const Color3 &op);

		Color3 &operator-=(const Color3 &rhs);
		Color3 operator-(const Color3 &op);

		Color3 &operator*=(const float scalar);
		Color3 operator*(const float scalar);

		Color3 &operator*=(const Color3 &rhs);
		Color3 operator*(const Color3 &op);

		Color3 &operator/=(const float scalar);
		Color3 operator/(const float scalar);

		Color3 &operator/=(const Color3 &rhs);
		Color3 operator/(const Color3 &op);

		bool operator==(const Color3 &other);
		bool operator!=(const Color3 &other);

		bool operator>(const Color3 &other);
		bool operator>=(const Color3 &other);

		bool operator<(const Color3 &other);
		bool operator<=(const Color3 &other);

		void Print();

		static Color3 Red;		static Color3 Yellow;	
		static Color3 Green;	static Color3 Cyan;
		static Color3 Blue;		static Color3 Magenta;
		static Color3 White;	static Color3 Gray;

		float R;
		float G;
		float B;

	private:
	protected:
	};

	class ATOMAPI Color4 {
	public:
		Color4();
		Color4(float red, float green, float blue, float alpha);
		~Color4();

		Color4 &operator=(const Color4 &rhs);

		Color4 &operator+=(const Color4 &rhs);
		Color4 operator+(const Color4 &op);

		Color4 &operator-=(const Color4 &rhs);
		Color4 operator-(const Color4 &op);

		Color4 &operator*=(const float scalar);
		Color4 operator*(const float scalar);

		Color4 &operator*=(const Color4 &rhs);
		Color4 operator*(const Color4 &op);

		Color4 &operator/=(const float scalar);
		Color4 operator/(const float scalar);

		Color4 &operator/=(const Color4 &rhs);
		Color4 operator/(const Color4 &op);

		bool operator==(const Color4 &other);
		bool operator!=(const Color4 &other);

		bool operator>(const Color4 &other);
		bool operator>=(const Color4 &other);

		bool operator<(const Color4 &other);
		bool operator<=(const Color4 &other);

		void Print();

		static Color4 Red;		static Color4 Yellow;	
		static Color4 Green;	static Color4 Cyan;
		static Color4 Blue;		static Color4 Magenta;
		static Color4 White;	static Color4 Gray;

		float R;
		float G;
		float B;
		float A;

	private:
	protected:
	};

	/* class that holds the Transformation subsystem */
	class ATOMAPI Transformation : public Vector3, public Time {
	public:
		Transformation();
		~Transformation();

		virtual void SetColor(Color3 Color);
		virtual void SetColor(float Red, float Green, float Blue);
		Color3 GetColor();

		void SetPosition(Vector3 pos);
		void SetPosition(float x, float y, float z);
		Vector3 GetPosition();

		virtual void SetScale(Vector3 scl);
		virtual void SetScale(float sclX, float sclY, float sclZ);
		Vector3 GetScale();

		void SetRotation(float angle, Vector3 rotationAxis);
		float GetAngle();
		Vector3 GetRotationAxis();

	private:
	protected:
		Color3 color;
		Vector3 position;
		Vector3 scale;
		float angleRot; Vector3 axis;
	};
}

#endif