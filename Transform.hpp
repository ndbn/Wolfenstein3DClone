#pragma once

#include "Matrix4f.hpp"
#include "Vector3f.hpp"
#include "Camera.hpp"


class Transform
{
public:
	explicit Transform(const Vector3f& pos = {}, const Vector3f& rot = {}, const Vector3f& scale = { 1, 1, 1 });

	static void setProjection(float fov, float width, float height, float zNear, float zFar)
	{
		Transform::mFov = fov;
		Transform::mWidth = width;
		Transform::mHeight = height;
		Transform::mZNear = zNear;
		Transform::mZFar = zFar;
	}

	static void setCamera(Camera& camera)
	{
		mCamera = &camera;
	}

	static Camera& getCamera() { return *mCamera; }

	Matrix4f getTransformation() const;
	Matrix4f getProjectedTransformation() const;

	inline Vector3f getPosition() const { return mPosition; }
	inline Vector3f getRotation() const { return mRotate; }
	inline Vector3f getScale() const { return mScale; }

	inline void setPosition(const Vector3f& pos) { mPosition = pos; }
	inline void setRotation(const Vector3f& rot) { mRotate = rot; }
	inline void setScale(const Vector3f& scale) { mScale = scale; }


private:
	Vector3f mPosition;
	Vector3f mRotate;
	Vector3f mScale;

	static Camera* mCamera;

	static float mFov;
	static float mWidth;
	static float mHeight;
	static float mZNear;
	static float mZFar;
};