#include "Camera.hpp"

Camera::Camera(const Vector3f& pos, const Vector3f& forward, const Vector3f& up)
	: mPosition(pos)
	, mForward(forward)
	, mUp(up)
{
	mForward.normalized();
	mUp.normalized();
}

void Camera::move(const Vector3f& direction, float amt)
{
	mPosition += (direction * amt);
}

void Camera::rotateY(float angle)
{
	Vector3f hAxis = UP.cross(mForward).normalized();

	mForward = mForward.rotate(angle, UP).normalized();
	mUp = mForward.cross(hAxis).normalized();
}

void Camera::rotateX(float angle)
{
	Vector3f hAxis = UP.cross(mForward).normalized();

	mForward = mForward.rotate(angle, hAxis).normalized();
	mUp = mForward.cross(hAxis).normalized();
}
