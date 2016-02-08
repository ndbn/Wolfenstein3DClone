#include "Mesh.hpp"
#include <GL/glew.h>

Mesh::Mesh()
{
	glGenBuffers(1, &mVbo);
	glGenBuffers(1, &mIbo);
	mSize = 0;
}

Mesh::~Mesh()
{
	glDeleteBuffers(1, &mVbo);
	glDeleteBuffers(1, &mIbo);
}

void Mesh::addVertices(Vertex* vertices, unsigned int vertSize, unsigned int* indices, unsigned int indexSize, bool needCalcNormals)
{
	mSize = indexSize;

	if(needCalcNormals)
		calcNormals(vertices, vertSize, indices, indexSize);

	glBindBuffer(GL_ARRAY_BUFFER, mVbo);
	glBufferData(GL_ARRAY_BUFFER, vertSize * sizeof(Vertex), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIbo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexSize * sizeof(int), indices, GL_STATIC_DRAW);
}

void Mesh::addVertices(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices, bool needCalcNormals)
{
	mSize = indices.size();

	if (needCalcNormals)
		calcNormals(vertices.data(), vertices.size(), indices.data(), indices.size());

	glBindBuffer(GL_ARRAY_BUFFER, mVbo);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vertices[0]), vertices.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIbo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(indices[0]), indices.data(), GL_STATIC_DRAW);
}

void Mesh::draw() const
{
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, mVbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)sizeof(Vector3f));
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(sizeof(Vector3f) + sizeof(Vector2f)));

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIbo);
	glDrawElements(GL_TRIANGLES, mSize, GL_UNSIGNED_INT, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
}

void Mesh::calcNormals(Vertex* vertices, unsigned int vertSize, unsigned int* indices, unsigned int indexSize)
{
	for(unsigned int i = 0; i < indexSize; i += 3)
	{
		int i0 = indices[i];
		int i1 = indices[i + 1];
		int i2 = indices[i + 2];
			
		Vector3f v1 = vertices[i1].position - vertices[i0].position;
		Vector3f v2 = vertices[i2].position - vertices[i0].position;
		
		Vector3f normal = v1.cross(v2).normalized();
		
		vertices[i0].normal += normal;
		vertices[i1].normal += normal;
		vertices[i2].normal += normal;
	}
	
	for(unsigned int i = 0; i < vertSize; i++)
		vertices[i].normal = vertices[i].normal.normalized();
}