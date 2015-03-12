#include "Mesh.h"
#include "Texture.h"
using namespace rb;
Mesh::Mesh(const std::vector<Vertex>& _vertices, const std::vector<GLuint>& _indices, const std::vector<Texture>& _textures)
	:vertices(_vertices),
	indices(_indices),
	textures(_textures)
{
}

Mesh::~Mesh()
{
}

void Mesh::Render() const
{
	
}
