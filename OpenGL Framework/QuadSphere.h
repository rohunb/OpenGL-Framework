#pragma once
#include "Model.h"
//////////////////////////////////////////////////////////////////////////
#include "Camera.h"

class QuadSphere : 	public Model
{
public:
	QuadSphere(int numSubDivisions, Shader* shader, Material material);
	~QuadSphere();

	void Render(Camera* camera) const;// override;

private:
	GLuint VAO, VBO;
	int numVertices;
	int index;
	glm::vec3 *vertex;
	glm::vec3 *normals;
	glm::vec2 *texCoords;
	GLint shaderProgram;
	GLint modelLoc, viewLoc, projLoc;
	Shader* shader;
	Material material;

	void LoadFace(const glm::vec3& a, const glm::vec3& b, const glm::vec3& c, const glm::vec3& d);
	void DivideFace(const glm::vec3& a, const glm::vec3& b, const glm::vec3& c, const glm::vec3& d, int count);
	void SphericalNormals();
};

