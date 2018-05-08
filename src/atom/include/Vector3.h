/*
* Copyright (C) 2012 PixelSquareLabs - All Rights Reserved
*
* Created: 06/05/2018
* Author:  Anthony Ganzon
* Email:   pixelsquarelabs@yahoo.com
*          pixelsquarelabs@gmail.com
*/

#ifndef _ATOMENGINE_VECTOR3_LIBRARY_H_
#define _ATOMENGINE_VECTOR3_LIBRARY_H_

#include "PlatformMacros.h"

ATOM_BEGIN

class ATOMAPI Vector3 
{
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

    static Vector3 ZERO;	static Vector3 FRONT;
    static Vector3 ONE;		static Vector3 BACK;
    static Vector3 UP;		static Vector3 RIGHT;
    static Vector3 DOWN;	static Vector3 LEFT;

    float x;
    float y;
    float z;
private:
protected:
};

ATOM_END

#endif