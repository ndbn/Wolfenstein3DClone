#pragma once

#include "Vector3f.hpp"
#include "Matrix4f.hpp"
#include "Material.hpp"

#include <SFML/System/NonCopyable.hpp>

#include <map>
#include <vector>
#include <string>

class Camera;

class Shader : private sf::NonCopyable
{
public:
	Shader();
	virtual ~Shader();

	void bind();

	void addUniform(const std::string& uniform);

	void addVertexShaderFromFile(const std::string& text);
	void addGeometryShaderFromFile(const std::string& text);
	void addFragmentShaderFromFile(const std::string& text);

	void addVertexShader(const std::string& text);
	void addGeometryShader(const std::string& text);
	void addFragmentShader(const std::string& text);

	void compileShader();

	virtual void updateUniforms(const Matrix4f& projectedMatrix, const Material& material);

	void setAttribLocation(const std::string& attributeName, int location);

	void setUniform(const std::string& name, int value);
	void setUniform(const std::string& name, float value);
	void setUniform(const std::string& name, const Vector3f& value);
	void setUniform(const std::string& name, const Matrix4f& value);

private:
	void addProgram(const std::string& text, int type);

	void checkShaderError(unsigned int shader, int flag, bool isProgram, const std::string& errorMessage);
	std::string loadShader(const std::string& fileName);

private:
	unsigned int mProgram;
	std::map<std::string, unsigned int> mUniforms;
	std::vector<int> mShaders;
};