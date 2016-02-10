#include "Level.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>


Level::Level(sf::RenderWindow& window, const std::string& map, const std::string& textures)
	: mWindow(window)
	, mMesh()
	, mShader()
	, mMaterial(textures)
	, mTransform()
	, mMap()
	, mDoors()
	, mPlayer(*this, { 7, 0.4375f, 7 })
{
	if (!mMap.loadFromFile("res/bitmaps/" + map))
		throw std::runtime_error("can't load map");

	generateLevel();
}

void Level::update(sf::Time dt)
{
	static const float OPEN_DISTANCE = 1.0f;

	for (auto& door : mDoors)
	{
		door->update(dt);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::E) /*&& run*/)
		{
			Vector3f delta = door->getPosition() - mPlayer.getCamera().getPosition();
			if (delta.length() < OPEN_DISTANCE)
				door->open(dt);
		}
	}

	mPlayer.update(dt, mWindow);
}

void Level::draw()
{
	mShader.updateUniforms(mTransform.getProjectedTransformation(), mMaterial);

	mPlayer.draw();

	mMesh.draw();

	for (auto& door : mDoors)
		door->draw();
}

unsigned Level::createRGB(int r, int g, int b) const
{
	return ((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff);
}

Vector3f Level::checkCollision(const Vector3f& oldPos, const Vector3f& newPos, float objectWidth, float objectLength) const
{
	Vector2f collisionVector = { 1, 1 };
	Vector3f movementVector = newPos - oldPos;

	if (movementVector.length() > 0)
	{
		Vector2f blockSize = { SPOT_WIDTH, SPOT_LENGTH };
		Vector2f objectSize = { objectWidth, objectLength };

		Vector2f oldPos2 = { oldPos.x, oldPos.z };
		Vector2f newPos2 = { newPos.x, newPos.z };

		for (unsigned int i = 0; i < mMap.getSize().x; i++)
		{
			for (unsigned int j = 0; j < mMap.getSize().y; j++)
			{
				int r = mMap.getPixel(i, j).r;
				int g = mMap.getPixel(i, j).g;
				int b = mMap.getPixel(i, j).b;

				unsigned num = createRGB(r, g, b);

				if ((num & 0xFFFFFF) == 0)
				{
					Vector2f block(blockSize.x * static_cast<float>(i), blockSize.y * static_cast<float>(j));
					collisionVector *= rectCollide(oldPos2, newPos2, objectSize, block, blockSize);
				}
			}
		}

		for (auto& door : mDoors)
		{
			Vector2f doorSize = door->getSize();
			Vector3f doorPos3f = door->getPosition();
			Vector2f doorPos2f = { door->getPosition().x, door->getPosition().z };

			collisionVector *= rectCollide(oldPos2, newPos2, objectSize, doorPos2f, doorSize);
		}
	}

	return{ collisionVector.x, 0, collisionVector.y };
}

Vector2f Level::rectCollide(const Vector2f& oldPos, const Vector2f& newPos, const Vector2f& size1, const Vector2f& pos2, const Vector2f& size2) const
{
	Vector2f result;

	if (newPos.x + size1.x < pos2.x ||
		newPos.x - size1.x > pos2.x + size2.x * size2.x ||
		oldPos.y + size1.y < pos2.y ||
		oldPos.y - size1.y > pos2.y + size2.y * size2.y)
		result.x = 1;

	if (oldPos.x + size1.x < pos2.x ||
		oldPos.x - size1.x > pos2.x + size2.x * size2.x ||
		newPos.y + size1.y < pos2.y ||
		newPos.y - size1.y > pos2.y + size2.y * size2.y)
		result.y = 1;

	return result;
}

void Level::addFace(std::vector<unsigned int>& indices, unsigned int startLocation, bool direction)
{
	if (direction)
	{
		indices.emplace_back(startLocation + 2);
		indices.emplace_back(startLocation + 1);
		indices.emplace_back(startLocation + 0);
		indices.emplace_back(startLocation + 3);
		indices.emplace_back(startLocation + 2);
		indices.emplace_back(startLocation + 0);
	}
	else
	{
		indices.emplace_back(startLocation + 0);
		indices.emplace_back(startLocation + 1);
		indices.emplace_back(startLocation + 2);
		indices.emplace_back(startLocation + 0);
		indices.emplace_back(startLocation + 2);
		indices.emplace_back(startLocation + 3);
	}
}

std::array<float, 4> Level::calcTexCoords(unsigned int value)
{
	unsigned int texX = value / NUM_TEXTURES;
	unsigned int texY = texX % NUM_TEX_EXP;
	texX /= NUM_TEX_EXP;

	std::array<float, 4> result;;

	result[0] = 1.f - static_cast<float>(texX) / static_cast<float>(NUM_TEX_EXP);
	result[1] = result[0] - 1.f / static_cast<float>(NUM_TEX_EXP);
	result[3] = 1.f - static_cast<float>(texY) / static_cast<float>(NUM_TEX_EXP);
	result[2] = result[3] - 1.f / static_cast<float>(NUM_TEX_EXP);

	return result;
}

void Level::addVertices(std::vector<Vertex>& vertices, unsigned int i, unsigned int j, unsigned int offset, bool x, bool y, bool z, const std::array<float, 4>& texCoords)
{
	if (x && z)
	{
		vertices.emplace_back(Vertex({ i		* SPOT_WIDTH, offset	* SPOT_HEIGHT, j		* SPOT_LENGTH }, { texCoords[1], texCoords[3] }));
		vertices.emplace_back(Vertex({ (i + 1)	* SPOT_WIDTH, offset	* SPOT_HEIGHT, j		* SPOT_LENGTH }, { texCoords[0], texCoords[3] }));
		vertices.emplace_back(Vertex({ (i + 1)	* SPOT_WIDTH, offset	* SPOT_HEIGHT, (j + 1)	* SPOT_LENGTH }, { texCoords[0], texCoords[2] }));
		vertices.emplace_back(Vertex({ i		* SPOT_WIDTH, offset	* SPOT_HEIGHT, (j + 1)	* SPOT_LENGTH }, { texCoords[1], texCoords[2] }));
	}
	else if (x && y)
	{
		vertices.emplace_back(Vertex({ i		* SPOT_WIDTH, j			* SPOT_HEIGHT, offset	* SPOT_LENGTH }, { texCoords[1], texCoords[3] }));
		vertices.emplace_back(Vertex({ (i + 1)	* SPOT_WIDTH, j			* SPOT_HEIGHT, offset	* SPOT_LENGTH }, { texCoords[0], texCoords[3] }));
		vertices.emplace_back(Vertex({ (i + 1)	* SPOT_WIDTH, (j + 1)	* SPOT_HEIGHT, offset	* SPOT_LENGTH }, { texCoords[0], texCoords[2] }));
		vertices.emplace_back(Vertex({ i		* SPOT_WIDTH, (j + 1)	* SPOT_HEIGHT, offset	* SPOT_LENGTH }, { texCoords[1], texCoords[2] }));
	}
	else if (y && z)
	{
		vertices.emplace_back(Vertex({ offset	* SPOT_WIDTH, i			* SPOT_HEIGHT, j		* SPOT_LENGTH }, { texCoords[1], texCoords[3] }));
		vertices.emplace_back(Vertex({ offset	* SPOT_WIDTH, i			* SPOT_HEIGHT, (j + 1)	* SPOT_LENGTH }, { texCoords[0], texCoords[3] }));
		vertices.emplace_back(Vertex({ offset	* SPOT_WIDTH, (i + 1)	* SPOT_HEIGHT, (j + 1)	* SPOT_LENGTH }, { texCoords[0], texCoords[2] }));
		vertices.emplace_back(Vertex({ offset	* SPOT_WIDTH, (i + 1)	* SPOT_HEIGHT, j		* SPOT_LENGTH }, { texCoords[1], texCoords[2] }));
	}
	else
	{
		throw std::runtime_error("Invalid plane used in level generator");
	}
}

void Level::addDoor(unsigned int x, unsigned int y)
{
	static const float DOOR_OPEN_MOVEMENT_AMOUNT = 0.9f;

	Vector3f doorPosition;
	Vector3f doorRotation;

	bool xDoor = (mMap.getPixel(x, y - 1)  == sf::Color::Black) && (mMap.getPixel(x, y + 1) == sf::Color::Black);
	bool yDoor = (mMap.getPixel(x - 1, y) == sf::Color::Black) && (mMap.getPixel(x + 1, y) == sf::Color::Black);

	if (!(xDoor ^ yDoor))
		throw std::runtime_error("Level Generation has failed! adding doors");

	if (yDoor)
		doorPosition = { (float)x, 0, y + SPOT_LENGTH / 2 };

	if (xDoor)
	{
		doorPosition = { x + SPOT_WIDTH / 2, 0, (float)y };
		doorRotation = { 0, 90, 0 };
	}

	mDoors.emplace_back(std::make_unique<Door>(doorPosition, doorRotation, mMaterial));
}

void Level::addSpecial(unsigned int blueValue, unsigned int x, unsigned int y)
{
	if (blueValue == 16)
		addDoor(x, y);
}

void Level::generateLevel()
{
	unsigned int width = mMap.getSize().x;
	unsigned int height = mMap.getSize().y;

	mMap.flipVertically();

	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;

	for (unsigned int i = 0; i < width; ++i)
	{
		for (unsigned int j = 0; j < height; ++j)
		{
			unsigned r = mMap.getPixel(i, j).r;
			unsigned g = mMap.getPixel(i, j).g;
			unsigned b = mMap.getPixel(i, j).b;

			unsigned num = createRGB(r, g, b);

			if ((num & 0xFFFFFF) == 0)
				continue;

			std::array<float, 4> texCoords(calcTexCoords(((num & 0x00FF00) >> 8)));

			addSpecial((num & 0x0000FF), i, j);

			//Generate Floor
			addFace(indices, vertices.size(), true);
			addVertices(vertices, i, j, 0, true, false, true, texCoords);

			//Generate Ceiling
			addFace(indices, vertices.size(), false);
			addVertices(vertices, i, j, 1, true, false, true, texCoords);

			//Generate Walls
			texCoords = calcTexCoords((num & 0xFF0000) >> 16);

			if (mMap.getPixel(i, j - 1) == sf::Color::Black)
			{
				addFace(indices, vertices.size(), false);
				addVertices(vertices, i, 0, j, true, true, false, texCoords);
			}

			if (mMap.getPixel(i, j + 1) == sf::Color::Black)
			{
				addFace(indices, vertices.size(), true);
				addVertices(vertices, i, 0, (j + 1), true, true, false, texCoords);
			}

			if (mMap.getPixel(i - 1, j) == sf::Color::Black)
			{
				addFace(indices, vertices.size(), true);
				addVertices(vertices, 0, j, i, false, true, true, texCoords);
			}

			if (mMap.getPixel(i + 1, j) == sf::Color::Black)
			{
				addFace(indices, vertices.size(), false);
				addVertices(vertices, 0, j, (i + 1), false, true, true, texCoords);
			}
		}
	}

	mMesh.addVertices(vertices, indices);
}