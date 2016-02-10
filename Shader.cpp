#include "Shader.hpp"
#include <cassert>
#include <fstream>
#include <iostream>
#include <GL/glew.h>

#include "Utility.hpp"


Shader::Shader()
	: mProgram(glCreateProgram())
	, mUniforms()
	, mShaders()
{
	if (mProgram == 0)
		throw std::runtime_error("Error creating shader program ");
}

Shader::~Shader()
{
	for(auto i : mShaders) 
	{
		glDetachShader(mProgram,i);
		glDeleteShader(i);
	}
	glDeleteProgram(mProgram);
}

void Shader::bind()
{
	glUseProgram(mProgram);
}

void Shader::addUniform(const std::string& uniform)
{
	int location = glGetUniformLocation(mProgram, uniform.c_str());

	assert(location != INVALID_VALUE);

	mUniforms.emplace(uniform, location);
}

void Shader::addVertexShaderFromFile(const std::string& text)
{
	addVertexShader(loadShader(text));
}

void Shader::addGeometryShaderFromFile(const std::string& text)
{
	addGeometryShader(loadShader(text));
}

void Shader::addFragmentShaderFromFile(const std::string& text)
{
	addFragmentShader(loadShader(text));
}

void Shader::addVertexShader(const std::string& text)
{
	addProgram(text, GL_VERTEX_SHADER);
}

void Shader::addGeometryShader(const std::string& text)
{
	addProgram(text, GL_GEOMETRY_SHADER);
}

void Shader::addFragmentShader(const std::string& text)
{
	addProgram(text, GL_FRAGMENT_SHADER);
}

void Shader::addProgram(const std::string& text, int type)
{
	unsigned int shader = glCreateShader(type);

	if(shader == 0)
		throw std::runtime_error("Error creating shader type " + std::to_string(type));


	const GLchar* p[1];
	p[0] = text.c_str();
	GLint lengths[1];
	lengths[0] = text.length();

	glShaderSource(shader, 1, p, lengths);
	glCompileShader(shader);
	checkShaderError(shader, GL_COMPILE_STATUS, false, "Error compiling shader type");

	glAttachShader(mProgram, shader);
	mShaders.push_back(shader);
}

void Shader::compileShader()
{
    glLinkProgram(mProgram);
	checkShaderError(mProgram, GL_LINK_STATUS, true, "Error linking shader program");

    glValidateProgram(mProgram);
	checkShaderError(mProgram, GL_VALIDATE_STATUS, true, "Invalid shader program");
}

void Shader::updateUniforms(const Matrix4f& projectedMatrix, const Material& material)
{
}

void Shader::setAttribLocation(const std::string& attributeName, int location)
{
	glBindAttribLocation(mProgram, location, attributeName.c_str());
}

void Shader::setUniform(const std::string& name, int value)
{
	glUniform1i(mUniforms.at(name), value);
}

void Shader::setUniform(const std::string& name, float value)
{
	glUniform1f(mUniforms.at(name), value);
}

void Shader::setUniform(const std::string& name, const Vector3f& value)
{
	glUniform3f(mUniforms.at(name), value.x, value.y, value.z);
}

void Shader::setUniform(const std::string& name, const Matrix4f& value)
{
	glUniformMatrix4fv(mUniforms.at(name), 1, GL_TRUE, &(value[0][0]));
}

void Shader::checkShaderError(unsigned int shader, int flag, bool isProgram, const std::string& errorMessage)
{
	GLint success = 0;
    GLchar error[1024] = { 0 };

	if(isProgram)
		glGetProgramiv(shader, flag, &success);
	else
		glGetShaderiv(shader, flag, &success);

	if(!success)
	{
		if(isProgram)
			glGetProgramInfoLog(shader, sizeof(error), NULL, error);
		else
			glGetShaderInfoLog(shader, sizeof(error), NULL, error);

		std::cerr << errorMessage.c_str() << ": " <<  error;
	}
}

std::string Shader::loadShader(const std::string& fileName)
{
	std::ifstream ifs("res/shaders/" + fileName);

	if (!ifs)
		throw std::runtime_error("cant load file: " + fileName);

	return std::string(std::istreambuf_iterator<char>(ifs),	std::istreambuf_iterator<char>());
};
