#pragma once
#include "glm\glm.hpp"
#include "Model.h"
#include <vector>

enum PrimitiveType { Cube, Sphere, QuadSphere };

class SimpleModel : public Model
{
public:

	SimpleModel(PrimitiveType type, Shader* shader, Material material);
	~SimpleModel();

	void Render() const override;

private:
	PrimitiveType type;

	GLuint VAO, VBO, EBO;

	int numVertices;
	int index;
	int numIndices;
	
	std::vector<GLfloat> vertices;
	std::vector<GLfloat> normals;
	std::vector<GLuint> indices;
	
	glm::vec3 *vertex;
	std::vector <glm::vec3> Qvertices;
	glm::vec3 *Qnormals;
	glm::vec2 *QtexCoords;

	void SetupCube();
	void SetupSphere();
	void SetupQuadSphere();

	void LoadFace(const glm::vec3& a, const glm::vec3& b, const glm::vec3& c, const glm::vec3& d);
	void DivideFace(const glm::vec3& a, const glm::vec3& b, const glm::vec3& c, const glm::vec3& d, int count);
	void SphericalNormals();

};

