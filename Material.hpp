#pragma once

#include "Texture.hpp"
#include "Vector3f.hpp"

struct Material
{
	Texture texture;
	Vector3f color;

	Material(const std::string& filename, const Vector3f& color = { 1,1,1 })
		: texture(filename)
		, color(color)
	{
	}
};