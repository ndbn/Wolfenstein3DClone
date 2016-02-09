#include "World.hpp"
#include "Utility.hpp"
#include "Vertex.hpp"

#include <SFML/Graphics/RenderWindow.hpp>


World::World(sf::RenderWindow& window)
	: mWindow(window)
	, mLevel("levelTest.png", "WolfCollection.png")
	, mPlayer(mLevel, {7, 0.4375f, 7})
{
	Transform::setCamera(mPlayer.getCamera());
	Transform::setProjection(70.f, static_cast<float>(window.getSize().x), static_cast<float>(window.getSize().y), 0.01f, 1000.f);
}

void World::update(sf::Time dt)
{
	mLevel.update(dt);
	mPlayer.update(dt, mWindow);
}

void World::draw()
{
	mLevel.draw();
	mPlayer.draw();
}