#include "QuadSphere.h"
#include <stdio.h>
//////////////////////////////////////////////////////////////////////////
#include "Camera.h"
#include <glm\gtc\type_ptr.hpp>
#include <vector>
#include "Material.h"
#include "Shader.h"

using namespace rb;
QuadSphere::QuadSphere(int numSubDivisions, Shader* _shader, Material _material)
{

	//shader = _shader;
	material = _material;

	numVertices = 6 * int(::pow(4.0, numSubDivisions + 1));
	index = 0;
	vertex = new glm::vec3[numVertices];
	normals = new glm::vec3[numVertices];
	texCoords = new glm::vec2[numVertices];

	glm::vec3 cube[8] = {
		///Front 4
		glm::vec3(-0.5, -0.5, 0.5),/// Left bottom
		glm::vec3(-0.5, 0.5, 0.5),/// Left top
		glm::vec3(0.5, 0.5, 0.5),/// Right top
		glm::vec3(0.5, -0.5, 0.5),/// Right bottom
		///Back 4
		glm::vec3(-0.5, -0.5, -0.5),
		glm::vec3(-0.5, 0.5, -0.5),
		glm::vec3(0.5, 0.5, -0.5),
		glm::vec3(0.5, -0.5, -0.5)
	};

	int count = numSubDivisions;
	if (count > 0){
		for (int j = 0; j < 8; ++j){
			cube[j] = glm::normalize(cube[j]);
		}
	}
	/// using the GL_QUADS method of drawing so I'll need specify cube 1234
	DivideFace(cube[1], cube[0], cube[3], cube[2], count); /// Front face
	DivideFace(cube[2], cube[3], cube[7], cube[6], count); /// Right face
	DivideFace(cube[3], cube[0], cube[4], cube[7], count); /// Bottom face
	DivideFace(cube[6], cube[5], cube[1], cube[2], count); /// Top face
	DivideFace(cube[4], cube[5], cube[6], cube[7], count); /// Back face
	DivideFace(cube[5], cube[4], cube[0], cube[1], count); /// Left face

	SphericalNormals();
	printf("%d vs %d\n", index, numVertices);

	std::vector <glm::vec3> vertices;
	for (int i = 0; i < numVertices; i+=4)
	{
		glm::vec3 one = vertex[i]; 
		glm::vec3 two = vertex[i + 1];
		glm::vec3 three = vertex[i + 2];
		glm::vec3 four = vertex[i + 3];

		vertices.push_back(one);
		vertices.push_back(two);
		vertices.push_back(three);

		vertices.push_back(one);
		vertices.push_back(three);
		vertices.push_back(four);
	}

//#define VERTEX_LENGTH 	( * (sizeof(glm::vec3)))
//#define NORMAL_LENGTH 	(numVertices * (sizeof(glm::vec3)))
//#define TEXCOORD_LENGTH (numVertices * (sizeof(glm::vec2)))

	const GLsizeiptr vertexLength = vertices.size()*sizeof(glm::vec3);
	const GLsizeiptr normalLength = numVertices * sizeof(glm::vec3);
	const GLsizeiptr texCoordLength = numVertices * sizeof(glm::vec2);

	numVertices = vertices.size();
	
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertexLength + normalLength + texCoordLength, NULL, GL_STATIC_DRAW);

	glEnableVertexAttribArray(Shader::VertexAttrib);
	glBufferSubData(GL_ARRAY_BUFFER, 0, vertexLength, &vertices[0]);
	glVertexAttribPointer(Shader::VertexAttrib, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);

	glEnableVertexAttribArray(Shader::NormalAttrib);
	glBufferSubData(GL_ARRAY_BUFFER, vertexLength, normalLength, normals);
	glVertexAttribPointer(Shader::NormalAttrib, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)texCoordLength);

	glEnableVertexAttribArray(Shader::TexCoordAttrib);
	glBufferSubData(GL_ARRAY_BUFFER, vertexLength + normalLength, texCoordLength, texCoords);
	glVertexAttribPointer(Shader::TexCoordAttrib, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*)(vertexLength + normalLength));



	////////////////////////
	/*shader = new Shader("lit_untextured_Shader.vert", "lit_untextured_Shader.frag");
	shader->HandleStdUniforms("uModel", "uView", "uProjection");
	modelLoc = shader->GetStdUniformLoc(ModelMatrix);
	viewLoc = shader->GetStdUniformLoc(ViewMatrix);
	projLoc = shader->GetStdUniformLoc(ProjectionMatrix);*/

	//viewLoc = glGetUniformLocation(shader->Program(), "uView");
	
	glBindVertexArray(0);
}


QuadSphere::~QuadSphere()
{

}

void QuadSphere::Render(Camera* camera) const
{
	///////////////////////
	//glUseProgram(shader->Program());
	//

	//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(glm::mat4(1.0f)));
	//glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(camera->View()));
	//glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(camera->Projection()));

	//glUniform3f(glGetUniformLocation(shader->Program(), "uViewPos"), 0.0f, 1.0f, 5.0f);

	////material
	//glUniform3f(glGetUniformLocation(shader->Program(), "uMaterial.diffuse"), material.diffuse.x, material.diffuse.y, material.diffuse.z);
	//glUniform3f(glGetUniformLocation(shader->Program(), "uMaterial.specular"), material.specular.x, material.specular.y, material.specular.z);
	//glUniform1f(glGetUniformLocation(shader->Program(), "uMaterial.shininess"), material.shininess);
	////light
	//glUniform3f(glGetUniformLocation(shader->Program(), "uLight.position"), 0.0f, 1.0f, 4.0f);
	//glUniform3f(glGetUniformLocation(shader->Program(), "uLight.ambient"), 1.0f, 0.0f, 0.0f);
	//glUniform3f(glGetUniformLocation(shader->Program(), "uLight.diffuse"), 1.0f, 1.0f, 1.0f);
	//glUniform3f(glGetUniformLocation(shader->Program(), "uLight.specular"), 1.0f, 1.0f, 1.0f);

	///////////////////
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, numVertices);
	glBindVertexArray(0);


	//////
	//glUseProgram(0);
}

void QuadSphere::LoadFace(const glm::vec3& a, const glm::vec3& b, const glm::vec3& c, const glm::vec3& d)
{
	glm::vec3 u = b - a;
	glm::vec3 v = c - b;
	glm::vec3 normal = glm::normalize((glm::cross(u, v)));
	//printf("u: %f %f %f v: %f %f %f\n", u.x,u.y, u.z, v.x, v.y, v.z);
	//printf("normal: %f %f %f\n", normal.x, normal.y, normal.z);
	normals[index] = normal;
	vertex[index] = a;
	texCoords[index][0] = 0.0; texCoords[index][1] = 0.0;
	index++;

	normals[index] = normal;
	vertex[index] = b;
	texCoords[index][0] = 0.0; texCoords[index][1] = 1.0;
	index++;

	normals[index] = normal;
	vertex[index] = c;
	texCoords[index][0] = 1.0; texCoords[index][1] = 1.0;
	index++;


	normals[index] = normal;
	vertex[index] = d;
	texCoords[index][0] = 1.0; texCoords[index][1] = 0.0;
	index++;
}

void QuadSphere::DivideFace(const glm::vec3& a, const glm::vec3& b, const glm::vec3& c, const glm::vec3& d, int count)
{
	if (count > 0){
		glm::vec3 v1 = glm::normalize(a + b);
		glm::vec3 v2 = glm::normalize(b + c);
		glm::vec3 v3 = glm::normalize(c + d);
		glm::vec3 v4 = glm::normalize(d + a);
		glm::vec3 vc = glm::normalize(a + c);
		DivideFace(a, v1, vc, v4, count - 1);
		DivideFace(v1, b, v2, vc, count - 1);
		DivideFace(vc, v2, c, v3, count - 1);
		DivideFace(v4, vc, v3, d, count - 1);
	}
	else{
		LoadFace(a, b, c, d);
	}
}

void QuadSphere::SphericalNormals()
{
	for (int j = 0; j < numVertices; ++j){
		normals[j] = glm::normalize(vertex[j]);
	}
}
