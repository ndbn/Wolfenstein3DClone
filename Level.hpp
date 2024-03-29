#pragma once

#include "Mesh.hpp"
#include "BasicShader.hpp"
#include "Transform.hpp"
#include "Material.hpp"
#include "Door.hpp"
#include "Player.hpp"

#include <SFML/System/NonCopyable.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/System/Time.hpp>
#include <array>
#include <memory>


class Level
{
	const float WIDTH = 1;
	const float LENGTH = 1;
	const float HEIGHT = 1;

	const int NUM_TEX_EXP = 4;
	const int NUM_TEXTURES = NUM_TEX_EXP * NUM_TEX_EXP;

public:
	Level(sf::RenderWindow& window, const std::string& map, const std::string& textures);

	void update(sf::Time dt);
	void draw();
	Vector3f checkCollision(const Vector3f& oldPos, const Vector3f&  newPos, float objectWidth, float objectLength) const;

	Camera& getCamera() { return mPlayer.getCamera(); }

private:
	// collision detection
	Vector2f rectCollide(const Vector2f& oldPos, const Vector2f& newPos, const Vector2f& size1, const Vector2f& pos2, const Vector2f& size2) const;
	// create level
	void addFace(std::vector<unsigned int>& indices, unsigned int startLocation, bool direction);
	std::array<float, 4> calcTexCoords(unsigned int value);
	void addVertices(std::vector<Vertex>& vertices, unsigned int i, unsigned int j, unsigned int offset, bool x, bool y, bool z, const std::array<float, 4>& texCoords);
	void addDoor(unsigned int x, unsigned int y);
	void addSpecial(unsigned int blueValue, unsigned int x, unsigned int y);
	void generateLevel();

private:
	sf::RenderWindow& mWindow;

	Mesh mMesh;
	BasicShader mShader;
	Material mMaterial;
	Transform mTransform;
	sf::Image mMap;
	std::vector<std::unique_ptr<Door>> mDoors;
	Player mPlayer;
};
