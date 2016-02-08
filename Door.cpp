#include "Door.hpp"
#include "Utility.hpp"


Door::Door(const Vector3f& poisition, const Vector3f& rotation, const Material& material)
	: mTransform(poisition, rotation)
	, mShader()
	, mMaterial(material) 
{
	Vertex vertices[] =
	{
		{ { START,START,START },{ 0.5f,1 } },
		{ { START,HEIGHT,START },{ 0.5f,0.75f } },
		{ { LENGTH,HEIGHT,START },{ 0.75f,0.75f } },
		{ { LENGTH,START,START },{ 0.75f,1 } },

		{ { START,START,START },{ 0.73f,1 } },
		{ { START,HEIGHT,START },{ 0.73f,0.75f } },
		{ { START,HEIGHT,WIDTH },{ 0.75f,0.75f } },
		{ { START,START,WIDTH },{ 0.75f,1 } },

		{ { START,START,WIDTH },{ 0.5f,1 } },
		{ { START,HEIGHT,WIDTH },{ 0.5f,0.75f } },
		{ { LENGTH,HEIGHT,WIDTH },{ 0.75f,0.75f } },
		{ { LENGTH,START,WIDTH },{ 0.75f,1 } },

		{ { LENGTH,START,START },{ 0.73f,1 } },
		{ { LENGTH,HEIGHT,START },{ 0.73f,0.75f } },
		{ { LENGTH,HEIGHT,WIDTH },{ 0.75f,0.75f } },
		{ { LENGTH,START,WIDTH },{ 0.75f,1 } }
	};

	unsigned int indices[] =
	{
		0, 1, 2,
		0, 2, 3,

		6, 5, 4,
		7, 6, 4,

		10, 9, 8,
		11, 10, 8,

		12, 13, 14,
		12, 14, 15
	};

	mMesh.addVertices(vertices, ARRAY_SIZE(vertices), indices, ARRAY_SIZE(indices));
}

void Door::update(sf::Time dt)
{

}

void Door::draw()
{
	mShader.updateUniforms(mTransform.getProjectedTransformation(), mMaterial);
	mMesh.draw();
}

Vector3f Door::getPosition() const
{
	return mTransform.getPosition();
}

Vector2f Door::getDoorSize() const
{
	return{ LENGTH, WIDTH };
}