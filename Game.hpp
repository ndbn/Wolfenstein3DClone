#pragma once

#include "World.hpp"

#include <SFML/Graphics/Text.hpp>

namespace sf
{
	class RenderWindow;
}

class Game : private sf::NonCopyable
{
public:
	explicit Game(sf::RenderWindow& window);
	void run();

private:
	void					processEvents();
	void					update(sf::Time elapsedTime);
	void					render();

	void					updateStatistics(sf::Time elapsedTime);


private:
	static const sf::Time	TimePerFrame;
	sf::RenderWindow&		mWindow;
	sf::Font				mFont;
	sf::Text				mStatisticsText;
	sf::Time				mStatisticsUpdateTime;

	std::size_t				mStatisticsNumFrames;
	World					mWorld;
};
