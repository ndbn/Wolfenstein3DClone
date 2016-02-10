#include "World.hpp"
#include "Utility.hpp"
#include "Vertex.hpp"

#include <SFML/Graphics/RenderWindow.hpp>


World::World(sf::RenderWindow& window)
	: mLevel(window, "levelTest.png", "WolfCollection.png")
{
	Transform::setCamera(mLevel.getCamera());
	Transform::setProjection(70.f, static_cast<float>(window.getSize().x), static_cast<float>(window.getSize().y), 0.01f, 1000.f);
}

void World::update(sf::Time dt)
{
	mLevel.update(dt);
}

void World::draw()
{
	mLevel.draw();
}