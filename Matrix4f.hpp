#pragma once

#include "Vector3f.hpp"

class Matrix4f 
{
public:
	void initIdentity();

	void initTranslationTransform(float x, float y, float z);
	void initRotateTransform(float rotateX, float rotateY, float rotateZ);
	void initScaleTransform(float scaleX, float scaleY, float scaleZ);
	void initPersProjTransform(float fov, float width, float height, float zNear, float zFar);
    void initCameraTransform(const Vector3f& target, const Vector3f& up);

	inline Matrix4f operator*(const Matrix4f& right) const
	{
		Matrix4f ret;
		for (unsigned int i = 0 ; i < 4 ; i++) 
		{
			for (unsigned int j = 0 ; j < 4 ; j++) 
			{
				ret.m[i][j] = m[i][0] * right.m[0][j] +
							  m[i][1] * right.m[1][j] +
							  m[i][2] * right.m[2][j] +
							  m[i][3] * right.m[3][j];
			}
		}
		return ret;
	}
	
	inline const float* operator[](int index) const { return m[index]; }
	inline float* operator[](int index) { return m[index]; }


private:
	float m[4][4];
};