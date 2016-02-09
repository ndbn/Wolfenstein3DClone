#include "Game.hpp"

#include <SFML/Graphics/RenderWindow.hpp>

#include <stdexcept>
#include <iostream>
#include <GL/glew.h>


int main()
{
	try
	{
		sf::ContextSettings settings;
		settings.depthBits = 24;
		settings.stencilBits = 8;
		settings.antialiasingLevel = 4;
		settings.majorVersion = 4;
		settings.minorVersion = 0;

		sf::RenderWindow window(sf::VideoMode(800, 600), "opengl template", sf::Style::Close, settings);

		glewExperimental = GL_TRUE;

		if (glewInit() != GLEW_OK)
			throw std::runtime_error("Failed to initialize GLEW\n");

		Game game(window);

		game.run();

	}
	catch (std::runtime_error& e)
	{
		std::cerr << "Exception: " << e.what() << std::endl;
		std::cin.ignore();
		return 1;
	}
}