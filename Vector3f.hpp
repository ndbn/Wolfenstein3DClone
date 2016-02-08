#pragma once

#include <cmath>

struct Vector3f
{
	Vector3f(float x = 0.0f, float y = 0.0f, float z = 0.0f) : x(x), y(y), z(z) {}

	inline float length() const { return std::sqrtf(x * x + y * y + z * z); }
	float dot(const Vector3f& v) const { return x * v.x + y * v.y + z * v.z; }

	inline Vector3f cross(const Vector3f& v) const
	{
		const float _x = y * v.z - z * v.y;
		const float _y = z * v.x - x * v.z;
		const float _z = x * v.y - y * v.x;

		return{ _x, _y, _z };
	}
	
	inline Vector3f rotate(float angle, const Vector3f& axis) const
	{
		const float sin = std::sinf(-angle);
		const float cos = std::cosf(-angle);
		
		return this->cross(axis * sin) +        //Rotation on local X
			(*this * cos) +                     //Rotation on local Z
		    axis * this->dot(axis * (1 - cos)); //Rotation on local Y
		
//		const float sinHalfAngle = std::sinf(angle/2);
//		const float cosHalfAngle = std::cosf(angle/2);
//
//		const float Rx = axis.x * sinHalfAngle;
//		const float Ry = axis.y * sinHalfAngle;
//		const float Rz = axis.z * sinHalfAngle;
//		const float Rw = cosHalfAngle;
//
//		Quaternion rotationQ(Rx, Ry, Rz, Rw);
//
//		Quaternion conjugateQ = rotationQ.conjugate();
//	  //  ConjugateQ.normalize();
//		Quaternion w = rotationQ * (*this) * conjugateQ;
//
//		return {w.x, w.y, w.z};
	}

	inline Vector3f normalized() const
	{
		const float len = length();

		return{ x / len, y / len, z / len };
	}

	inline Vector3f operator+(const Vector3f& r) const { return{ x + r.x, y + r.y, z + r.z }; }
	inline Vector3f operator-(const Vector3f& r) const { return{ x - r.x, y - r.y, z - r.z }; }
	inline Vector3f operator*(float f) const { return{ x * f, y * f, z * f }; }
	inline Vector3f operator/(float f) const { return{ x / f, y / f, z / f }; }

	inline bool operator==(const Vector3f& r) const { return x == r.x && y == r.y && z == r.z; }
	inline bool operator!=(const Vector3f& r) const { return !operator==(r); }
	
	inline Vector3f& operator+=(const Vector3f& r)
	{
		x += r.x;
		y += r.y;
		z += r.z;

		return *this;
	}
	
    inline Vector3f& operator-=(const Vector3f& r)
    {
		x -= r.x;
		y -= r.y;
		z -= r.z;

		return *this;
    }

	inline Vector3f& operator*=(const Vector3f& r)
	{
		x *= r.x;
		y *= r.y;
		z *= r.z;

		return *this;
	}

    inline Vector3f& operator*=(float f)
    {
		x *= f;
		y *= f;
		z *= f;

		return *this;
    }

	inline Vector3f& operator/=(float f)
	{
		x /= f;
		y /= f;
		z /= f;

		return *this;
	}
	
	inline void set(float x, float y, float z) { this->x = x; this->y = y; this->z = z; }

	float x,y,z;
};