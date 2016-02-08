#pragma once

#include "Vector3f.hpp"

#include <SFML/System/Time.hpp>
#include <SFML/System/NonCopyable.hpp>


class Camera : private sf::NonCopyable
{
	const Vector3f UP = { 0, 1, 0 };

public:
	explicit Camera(const Vector3f& pos = {}, const Vector3f& forward = { 0, 0, 1 }, const Vector3f& up = { 0, 1, 0 });

	void move(const Vector3f& direction, float amt);

	void rotateY(float angle);
	void rotateX(float angle);

	inline Vector3f getPosition() const
	{ 
		return mPosition;
	}

	inline Vector3f getForward() const
	{ 
		return mForward;
	}

	inline Vector3f getUp() const
	{ 
		return mUp;
	}

	inline Vector3f getLeft() const 
	{ 
		return mForward.cross(mUp).normalized();
	}

	inline Vector3f getRight() const 
	{ 
		return mUp.cross(mForward).normalized();
	}

private:
	Vector3f mPosition;
	Vector3f mForward;
	Vector3f mUp;
};
