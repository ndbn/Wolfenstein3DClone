#pragma once

#include <GL/glew.h>
#include <string>

#include <SFML/System/NonCopyable.hpp>


class Texture : private sf::NonCopyable
{
public:
	explicit Texture(const std::string& fileName, GLenum textureTarget = GL_TEXTURE_2D, GLfloat filter = GL_LINEAR);
	Texture(unsigned int width = 0, unsigned int height = 0, unsigned char* data = nullptr, GLenum textureTarget = GL_TEXTURE_2D, GLfloat filter = GL_LINEAR);
	~Texture();

	void bind(unsigned int unit = 0) const;


private:
	void initTexture(unsigned int width, unsigned int height, const unsigned char* data, GLenum textureTarget, GLfloat filter);


private:
	static const Texture* LastBind;

	GLenum mTextureTarget;
	GLuint mTextureID;
	bool mFreeTexture;
};