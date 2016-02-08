#include "BasicShader.hpp"
#include "Utility.hpp"


BasicShader::BasicShader()
{
	addVertexShaderFromFile("basicVertex.vs");
	addFragmentShaderFromFile("basicFragment.fs");

	setAttribLocation("position", 0);
	setAttribLocation("texCoord", 1);
	compileShader();

	addUniform("transform");
	addUniform("color");
}

void BasicShader::updateUniforms(const Matrix4f& projectedMatrix, const Material& material)
{
	bind();

	material.texture.bind();

	setUniform("transform", projectedMatrix);
	setUniform("color", material.color);
}