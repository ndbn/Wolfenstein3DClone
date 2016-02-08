#pragma once

#include "Mesh.hpp"
#include "BasicShader.hpp"
#include "Transform.hpp"
#include "Material.hpp"

class Door
{
	const float LENGTH = 1;
	const float HEIGHT = 1;
	const float WIDTH = 0.125f;
	const float START = 0;

public:
	explicit Door(const Vector3f& poisition, const Vector3f& rotation, const Material& material);

	void update(sf::Time dt);
	void draw();

	Vector3f getPosition() const;
	Vector2f getDoorSize() const;

private:
	Mesh mMesh;
	BasicShader mShader;
	const Material& mMaterial;
	Transform mTransform;
};