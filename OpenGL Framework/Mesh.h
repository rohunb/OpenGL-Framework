#pragma once
#include <vector>
#include <glm\glm.hpp>
#include <glew.h>

struct Vertex
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec3 texCoord;
};

class Mesh
{
public:
	Mesh(const std::vector<Vertex>& vertices, const std::vector<GLuint>& indices, const std::vector<struct Texture>& textures);
	~Mesh();
	void Render() const;

private:
	GLuint VAO, VBO, EBO;
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;
	std::vector<struct Texture> textures;
};

