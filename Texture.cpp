#include "Texture.hpp"

#include <SFML/Graphics/Image.hpp>
#include <cassert>


const Texture* Texture::LastBind = nullptr;


Texture::Texture(const std::string& fileName, GLenum textureTarget, GLfloat filter)
{
	sf::Image data;

	if (!data.loadFromFile("./res/textures/" + fileName))
		throw std::runtime_error("Unable to load texture: " + fileName);

	initTexture(data.getSize().x, data.getSize().y, data.getPixelsPtr(), textureTarget, filter);
}

Texture::Texture(unsigned int width, unsigned int height, unsigned char* data, GLenum textureTarget, GLfloat filter)
{
	initTexture(width, height, data, textureTarget, filter);
}

void Texture::initTexture(unsigned int width, unsigned int height, const unsigned char* data, GLenum textureTarget, GLfloat filter)
{
	mTextureTarget = textureTarget;
	mFreeTexture = true;
	
	if(width <= 0 && height <= 0 && data == nullptr)
		mTextureID = 0;

	glGenTextures(1, &mTextureID);
	glBindTexture(textureTarget, mTextureID);
	glTexParameterf(textureTarget, GL_TEXTURE_MIN_FILTER, filter);
	glTexParameterf(textureTarget, GL_TEXTURE_MAG_FILTER, filter);
	glTexImage2D(textureTarget, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
}

Texture::~Texture()
{
	if(mFreeTexture)
		glDeleteTextures(1, &mTextureID);
}

void Texture::bind(unsigned int unit) const
{
	if(LastBind != this)
	{
		assert(unit >= 0 && unit <= 31);
		glActiveTexture(GL_TEXTURE0 + unit);
		glBindTexture(mTextureTarget, mTextureID);
		LastBind = this;
	}
}
