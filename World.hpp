#pragma once

#include "Player.hpp"


namespace sf
{
	class RenderWindow;
}

class World : private sf::NonCopyable
{
public:
	explicit World(sf::RenderWindow& window);

	void update(sf::Time dt);
	void draw();

private:
	sf::RenderWindow& mWindow;
	Level mLevel;
	Player mPlayer;
};
