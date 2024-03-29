#pragma once

#include "Level.hpp"


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
	Level mLevel;
};
