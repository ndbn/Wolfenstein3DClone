#pragma once

#include "Vector3f.hpp"
#include "Vector2f.hpp"

struct Vertex
{
	Vector3f position;
	Vector2f texCoord;
	Vector3f normal;

	Vertex(Vector3f pos = {}, Vector2f texCoord = {}, Vector3f normal = {})
		: position(pos)
		, texCoord(texCoord)
		, normal(normal)
	{}
};