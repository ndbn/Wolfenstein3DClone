#pragma once

#include "Camera.hpp"
#include "Level.hpp"

namespace sf
{
	class RenderWindow;
}

class Player
{
	const Vector3f Zero = {};

public:
	explicit Player(const Level& mLevel, const Vector3f& position);

	void update(sf::Time dt, sf::RenderWindow& window);
	void draw();
	Camera& getCamera() { return mCamera; }


private:
	Camera mCamera;
	const Level& mLevel;
	bool mMouseLocked;
	Vector3f mMovement;
};
