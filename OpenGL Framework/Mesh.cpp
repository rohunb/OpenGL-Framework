#include "Mesh.h"
//#include "Texture.h"
#include "Material.h"
#include "Debug.h"
#include "Shader.h"

using namespace rb;
Mesh::Mesh(const std::vector<Vertex>& _vertices, const std::vector<GLuint>& _indices, const Material& _material)
	:vertices(_vertices),
	indices(_indices),
	material(_material)
{
	size_t vertexSize = sizeof(Vertex);
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * vertexSize, &vertices[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(static_cast<GLuint>(Shader::StdAttrib::VertexAttrib));
	glVertexAttribPointer(static_cast<GLuint>(Shader::StdAttrib::VertexAttrib), 3, GL_FLOAT, GL_FALSE, vertexSize, (GLvoid*)0);
	glEnableVertexAttribArray(static_cast<GLuint>(Shader::StdAttrib::NormalAttrib));
	glVertexAttribPointer(static_cast<GLuint>(Shader::StdAttrib::NormalAttrib), 3, GL_FLOAT, GL_FALSE, vertexSize, (GLvoid*)offsetof(Vertex, normal));
	glEnableVertexAttribArray(static_cast<GLuint>(Shader::StdAttrib::TexCoordAttrib));
	glVertexAttribPointer(static_cast<GLuint>(Shader::StdAttrib::TexCoordAttrib), 2, GL_FLOAT, GL_FALSE, vertexSize, (GLvoid*)offsetof(Vertex, uvCoord));
	glBindVertexArray(0);
}

Mesh::~Mesh()
{
}

void Mesh::Render() const
{
	assert(indices.size() > 0);
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}
