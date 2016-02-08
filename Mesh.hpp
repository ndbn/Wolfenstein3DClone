#pragma once

#include "Vertex.hpp"

#include <SFML/System/NonCopyable.hpp>

#include <vector>


class Mesh : private sf::NonCopyable
{
public:
	Mesh();
	~Mesh();

	void addVertices(Vertex* vertices, unsigned int vertSize, unsigned int* indices, unsigned int indexSize, bool calcNormals = true);
	void addVertices(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices, bool calcNormals = true);
	void draw() const;

private:
	void calcNormals(Vertex* vertices, unsigned int vertSize, unsigned int* indices, unsigned int indexSize);

	unsigned int mVbo;
	unsigned int mIbo;
	unsigned int mSize;
};