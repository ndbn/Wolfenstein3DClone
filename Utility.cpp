#include "Utility.hpp"

#include <GL/glew.h>


void utility::clearScreen()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void utility::initGraphics()
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	glFrontFace(GL_CW);
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_DEPTH_CLAMP);

	glEnable(GL_TEXTURE_2D);
}