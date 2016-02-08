#include "Transform.hpp"

Camera* Transform::mCamera = nullptr;

float Transform::mFov;
float Transform::mWidth;
float Transform::mHeight;
float Transform::mZNear;
float Transform::mZFar;

Transform::Transform(const Vector3f& pos, const Vector3f& rot, const Vector3f& scale)
	: mPosition(pos)
	, mRotate(rot)
	, mScale(scale)
{
}

Matrix4f Transform::getTransformation() const
{
	Matrix4f translationMatrix;
	Matrix4f rotationMatrix;
	Matrix4f scaleMatrix;

	translationMatrix.initTranslationTransform(mPosition.x, mPosition.y, mPosition.z);
	rotationMatrix.initRotateTransform(mRotate.x, mRotate.y, mRotate.z);
	scaleMatrix.initScaleTransform(mScale.x, mScale.y, mScale.z);

	return translationMatrix * rotationMatrix * scaleMatrix;
}

Matrix4f Transform::getProjectedTransformation() const
{
	Matrix4f transformationMatrix = getTransformation();
	Matrix4f projectionMatrix;
	Matrix4f cameraRotation;
	Matrix4f cameraTranslation;

	projectionMatrix.initPersProjTransform(mFov, mWidth, mHeight, mZNear, mZFar);
	cameraRotation.initCameraTransform(mCamera->getForward(), mCamera->getUp());
	cameraTranslation.initTranslationTransform(-mCamera->getPosition().x, -mCamera->getPosition().y, -mCamera->getPosition().z);

	return projectionMatrix * cameraRotation * cameraTranslation * transformationMatrix;

}
