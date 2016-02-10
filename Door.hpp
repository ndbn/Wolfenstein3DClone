#pragma once

#include "Mesh.hpp"
#include "BasicShader.hpp"
#include "Transform.hpp"
#include "Material.hpp"

class Door
{
	//const float LENGTH = 1;
	//const float HEIGHT = 1;
	//const float WIDTH = 0.125f;
	const float WIDTH = 1;
	const float HEIGHT = 1;
	const float LENGTH = 0.125f;
	const float START = 0;

	const float TIME_TO_OPEN = 0.25f;
	const float CLOSE_DELAY = 2.0f;

public:
	explicit Door(const Vector3f& poisition, const Vector3f& rotation, const Material& material);

	void open(sf::Time dt);
	void update(sf::Time dt);
	void draw();

	Vector3f getPosition() const;
	Vector2f getSize() const;

private:
	Mesh mMesh;
	BasicShader mShader;
	const Material& mMaterial;
	Transform mTransform;
	bool mIsOpening;

	Vector3f mOpenPosition;
	Vector3f mClosePosition;

	float mOpeningStartTime;
	float mOpenTime;
	float mClosingStartTime;
	float mCloseTime;
	sf::Time mTimer;
};