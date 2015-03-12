#include "SimpleModel.h"
#include <stdio.h>
#include <glm\gtc\constants.hpp>
using namespace rb;
SimpleModel::SimpleModel(PrimitiveType _type, Shader* _shader, Material _material)
	:type(_type)
{
	switch (type)
	{
	case Sphere:
		SetupSphere();
		break;
	case Cube:
		SetupCube();
		break;
	case QuadSphere:
		SetupQuadSphere();
		break;
	default:
		break;
	}
	shader = _shader;
	material = _material;
}


SimpleModel::~SimpleModel()
{

}

void SimpleModel::Render() const
{
	//printf("Simple Model render\n");
	glBindVertexArray(VAO);

	switch (type)
	{
	case Cube:
		glDrawArrays(GL_TRIANGLES, 0, 36);
		break;
	case Sphere:
		glDrawElements(GL_QUADS, indices.size(), GL_UNSIGNED_INT, 0);
		break;
	case QuadSphere:
		glDrawArrays(GL_TRIANGLES, 0, numVertices);
	default:
		break;
	}
	
	glBindVertexArray(0);

}
void SimpleModel::SetupQuadSphere()
{
	int numSubDivisions = 4;
	numVertices = 6 * int(::pow(4.0, numSubDivisions + 1));
	index = 0;
	vertex = new Vec3[numVertices];
	Qnormals = new Vec3[numVertices];
	QtexCoords = new glm::vec2[numVertices];

	Vec3 cube[8] = {
		///Front 4
		Vec3(-0.5, -0.5, 0.5),/// Left bottom
		Vec3(-0.5, 0.5, 0.5),/// Left top
		Vec3(0.5, 0.5, 0.5),/// Right top
		Vec3(0.5, -0.5, 0.5),/// Right bottom
		///Back 4
		Vec3(-0.5, -0.5, -0.5),
		Vec3(-0.5, 0.5, -0.5),
		Vec3(0.5, 0.5, -0.5),
		Vec3(0.5, -0.5, -0.5)
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

	
	for (int i = 0; i < numVertices; i += 4)
	{
		Vec3 one = vertex[i];
		Vec3 two = vertex[i + 1];
		Vec3 three = vertex[i + 2];
		Vec3 four = vertex[i + 3];

		Qvertices.push_back(one);
		Qvertices.push_back(two);
		Qvertices.push_back(three);

		Qvertices.push_back(one);
		Qvertices.push_back(three);
		Qvertices.push_back(four);
	}

	//#define VERTEX_LENGTH 	( * (sizeof(Vec3)))
	//#define NORMAL_LENGTH 	(numVertices * (sizeof(Vec3)))
	//#define TEXCOORD_LENGTH (numVertices * (sizeof(glm::vec2)))

	const GLsizeiptr vertexLength = Qvertices.size()*sizeof(Vec3);
	const GLsizeiptr normalLength = numVertices * sizeof(Vec3);
	const GLsizeiptr texCoordLength = numVertices * sizeof(glm::vec2);

	numVertices = Qvertices.size();

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertexLength + normalLength + texCoordLength, NULL, GL_STATIC_DRAW);

	glEnableVertexAttribArray(Shader::VertexAttrib);
	glBufferSubData(GL_ARRAY_BUFFER, 0, vertexLength, &Qvertices[0]);
	glVertexAttribPointer(Shader::VertexAttrib, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);

	glEnableVertexAttribArray(Shader::NormalAttrib);
	glBufferSubData(GL_ARRAY_BUFFER, vertexLength, normalLength, Qnormals);
	glVertexAttribPointer(Shader::NormalAttrib, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)texCoordLength);

	glEnableVertexAttribArray(Shader::TexCoordAttrib);
	glBufferSubData(GL_ARRAY_BUFFER, vertexLength + normalLength, texCoordLength, QtexCoords);
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
void SimpleModel::SetupCube()
{
#pragma region CubeVertices
	GLfloat cubeVertices[] = {
		// Positions	      // Normals	   // Texture Coords
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
		0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f,
		0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
		0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
		-0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,

		-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
		0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
		0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
		0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
		-0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,

		-0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
		-0.5f, 0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
		-0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,

		0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
		0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
		0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
		0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
		0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
		0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
		0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f,
		0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
		0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
		-0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,

		-0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
		0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
		0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
		0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
		-0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
		-0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f
	};
#pragma endregion

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

#define FLOAT_SIZE sizeof(GLfloat)
#define ARRAY_STRIDE 8
#define VERT_SIZE 3
#define UV_SIZE 2

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(Shader::VertexAttrib);
	glVertexAttribPointer(Shader::VertexAttrib, VERT_SIZE, GL_FLOAT, GL_FALSE, ARRAY_STRIDE*FLOAT_SIZE, (GLvoid*)0);
	glEnableVertexAttribArray(Shader::NormalAttrib);
	glVertexAttribPointer(Shader::NormalAttrib, VERT_SIZE, GL_FLOAT, GL_FALSE, ARRAY_STRIDE*FLOAT_SIZE, (GLvoid*)(VERT_SIZE*FLOAT_SIZE));
	glEnableVertexAttribArray(Shader::TexCoordAttrib);
	glVertexAttribPointer(Shader::TexCoordAttrib, UV_SIZE, GL_FLOAT, GL_FALSE, ARRAY_STRIDE*FLOAT_SIZE, (GLvoid*)(VERT_SIZE * 2 * FLOAT_SIZE));

	glBindVertexArray(0);

#undef FLOAT_SIZE
#undef ARRAY_STRIDE
#undef VERT_SIZE
#undef UV_SIZE


}
void SimpleModel::SetupSphere()
{
	float radius = 1.0f;
	int rings = 12;
	int sectors = 36;

	float const R = 1.0f / (float)(rings - 1);
	float const S = 1.0f / (float)(sectors - 1);
	int r, s;
	float pi = glm::pi<float>();
	vertices.resize(rings * sectors * 3);
	normals.resize(rings * sectors * 3);
	std::vector<GLfloat>::iterator v = vertices.begin();
	std::vector<GLfloat>::iterator n = normals.begin();
	for (r = 0; r < rings; r++)
	{
		for (s = 0; s < sectors; s++)
		{
			float const y = sin(-pi / 2.0f + pi * r * R);
			float const x = cos(2 * pi* s * S) * sin(pi * r * R);
			float const z = sin(2 * pi * s * S) * sin(pi * r * R);

			*v++ = x * radius;
			*v++ = y * radius;
			*v++ = z * radius;

			*n++ = x;
			*n++ = y;
			*n++ = z;
		}
	}
	indices.resize(rings * sectors * 4);
	std::vector<GLuint>::iterator i = indices.begin();
	for (r = 0; r < rings - 1; r++)
	{
		for (s = 0; s < sectors - 1; s++)
		{
			*i++ = r * sectors + s;
			*i++ = r * sectors + (s + 1);
			*i++ = (r + 1) * sectors + (s + 1);
			*i++ = (r + 1) * sectors + s;
		}
	}

	//numIndices = indices.size();

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	GLuint Norms;
	glGenBuffers(1, &Norms);
	glGenBuffers(1, &EBO);
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), &vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size()* sizeof(GLuint), &indices[0], GL_STATIC_DRAW);
	glVertexAttribPointer(Shader::VertexAttrib, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
	glEnableVertexAttribArray(Shader::VertexAttrib);

	glBindBuffer(GL_ARRAY_BUFFER, Norms);
	glBufferData(GL_ARRAY_BUFFER, normals.size()*sizeof(GLfloat), &normals[0], GL_STATIC_DRAW);
	glVertexAttribPointer(Shader::NormalAttrib, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
	glEnableVertexAttribArray(Shader::NormalAttrib);

	glBindVertexArray(0);
}

void SimpleModel::LoadFace(const Vec3& a, const Vec3& b, const Vec3& c, const Vec3& d)
{
	Vec3 u = b - a;
	Vec3 v = c - b;
	Vec3 normal = glm::normalize((glm::cross(u, v)));
	//printf("u: %f %f %f v: %f %f %f\n", u.x,u.y, u.z, v.x, v.y, v.z);
	//printf("normal: %f %f %f\n", normal.x, normal.y, normal.z);
	Qnormals[index] = normal;
	vertex[index] = a;
	QtexCoords[index][0] = 0.0; QtexCoords[index][1] = 0.0;
	index++;

	Qnormals[index] = normal;
	vertex[index] = b;
	QtexCoords[index][0] = 0.0; QtexCoords[index][1] = 1.0;
	index++;

	Qnormals[index] = normal;
	vertex[index] = c;
	QtexCoords[index][0] = 1.0; QtexCoords[index][1] = 1.0;
	index++;


	Qnormals[index] = normal;
	vertex[index] = d;
	QtexCoords[index][0] = 1.0; QtexCoords[index][1] = 0.0;
	index++;
}

void SimpleModel::DivideFace(const Vec3& a, const Vec3& b, const Vec3& c, const Vec3& d, int count)
{
	if (count > 0){
		Vec3 v1 = glm::normalize(a + b);
		Vec3 v2 = glm::normalize(b + c);
		Vec3 v3 = glm::normalize(c + d);
		Vec3 v4 = glm::normalize(d + a);
		Vec3 vc = glm::normalize(a + c);
		DivideFace(a, v1, vc, v4, count - 1);
		DivideFace(v1, b, v2, vc, count - 1);
		DivideFace(vc, v2, c, v3, count - 1);
		DivideFace(v4, vc, v3, d, count - 1);
	}
	else{
		LoadFace(a, b, c, d);
	}
}

void SimpleModel::SphericalNormals()
{
	for (int j = 0; j < numVertices; ++j){
		Qnormals[j] = glm::normalize(vertex[j]);
	}
}



//#define VERTEX_LENGTH vertices.size() * sizeof(Vec3)
//#define NORMAL_LENGTH normals.size() * sizeof(Vec3)
//#define INDICES_LENGTH indices.size() * sizeof(GLuint)
//
//	glGenVertexArrays(1, &VAO);
//	glGenBuffers(1, &VBO);
//	glGenBuffers(1, &EBO);
//
//	glBindVertexArray(VAO);
//	
//	glBindBuffer(GL_ARRAY_BUFFER, VBO);
//	glBufferData(GL_ARRAY_BUFFER, VERTEX_LENGTH + NORMAL_LENGTH, NULL, GL_STATIC_DRAW);
//
//	glEnableVertexAttribArray(VertexAttrib);
//	glBufferSubData(GL_ARRAY_BUFFER, 0, VERTEX_LENGTH, &vertices[0]);
//	glVertexAttribPointer(VertexAttrib, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
//
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//	glBufferData(GL_ELEMENT_ARRAY_BUFFER, INDICES_LENGTH, &indices[0], GL_STATIC_DRAW);
//
//	glEnableVertexAttribArray(NormalAttrib);
//	glBufferSubData(GL_ARRAY_BUFFER, VERTEX_LENGTH, NORMAL_LENGTH, &normals[0]);
//	glVertexAttribPointer(NormalAttrib, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)(VERTEX_LENGTH));
//
//	glBindVertexArray(0);
//
//#undef VERTEX_LENGTH
//#undef NORMAL_LENGTH
//#undef INDICES_LENGTH
//}

//void SimpleModel::SetupSphere()
//{
//	int numSubDivisions = 4;
//	numVertices = 6 * int(pow(4.0f, numSubDivisions + 1));
//	index = 0;
//	vertices = new Vec3[numVertices];
//	normals = new Vec3[numVertices];
//	texCoords = new glm::vec2[numVertices];
//	Vec3 cube[8] =
//	{
//		///Front 4
//		Vec3(-0.5, -0.5, 0.5),/// Left bottom
//		Vec3(-0.5, 0.5, 0.5),/// Left top
//		Vec3(0.5, 0.5, 0.5),/// Right top
//		Vec3(0.5, -0.5, 0.5),/// Right bottom
//		///Back 4
//		Vec3(-0.5, -0.5, -0.5),
//		Vec3(-0.5, 0.5, -0.5),
//		Vec3(0.5, 0.5, -0.5),
//		Vec3(0.5, -0.5, -0.5)
//	};
//	int count = numSubDivisions;
//	if (count > 0){
//		for (int j = 0; j < 8; ++j){
//			cube[j] = glm::normalize(cube[j]);
//		}
//	}
//	DivideFace(cube[1], cube[0], cube[3], cube[2], count); /// Front face
//	DivideFace(cube[2], cube[3], cube[7], cube[6], count); /// Right face
//	DivideFace(cube[3], cube[0], cube[4], cube[7], count); /// Bottom face
//	DivideFace(cube[6], cube[5], cube[1], cube[2], count); /// Top face
//	DivideFace(cube[4], cube[5], cube[6], cube[7], count); /// Back face
//	DivideFace(cube[5], cube[4], cube[0], cube[1], count); /// Left face
//
//	SphericalNormals();
//	printf("%d vs %d\n", index, numVertices);
//#define VERTEX_LENGTH 	(numVertices * (sizeof(Vec3)))
//#define NORMAL_LENGTH 	(numVertices * (sizeof(Vec3)))
//#define TEXCOORD_LENGTH (numVertices * (sizeof(glm::vec2)))
//
//	glGenVertexArrays(1, &VAO);
//	glBindVertexArray(VAO);
//
//	glGenBuffers(1, &VBO);
//	glBindBuffer(GL_ARRAY_BUFFER, VBO);
//	glBufferData(GL_ARRAY_BUFFER, VERTEX_LENGTH + NORMAL_LENGTH + TEXCOORD_LENGTH, NULL, GL_STATIC_DRAW);
//
//	glEnableVertexAttribArray(VertexAttrib);
//	glBufferSubData(GL_ARRAY_BUFFER, 0, VERTEX_LENGTH, vertices);
//	glVertexAttribPointer(VertexAttrib, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
//
//	glEnableVertexAttribArray(NormalAttrib);
//	glBufferSubData(GL_ARRAY_BUFFER, VERTEX_LENGTH, NORMAL_LENGTH, normals);
//	glVertexAttribPointer(NormalAttrib, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)VERTEX_LENGTH);
//
//	glEnableVertexAttribArray(TexCoordAttrib);
//	glBufferSubData(GL_ARRAY_BUFFER, VERTEX_LENGTH + NORMAL_LENGTH, TEXCOORD_LENGTH, texCoords);
//	glVertexAttribPointer(TexCoordAttrib, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*)(VERTEX_LENGTH + NORMAL_LENGTH));
//
//#undef VERTEX_LENGTH
//#undef NORMAL_LENGTH
//#undef TEXCOORD_LENGTH
//}

//
//void SimpleModel::LoadFace(const Vec3& a, const Vec3& b, const Vec3& c, const Vec3& d)
//{
//	Vec3 u = b - a;
//	Vec3 v = c - b;
//	Vec3 normal = glm::normalize((glm::cross(u, v)));
//	//printf("u: %f %f %f v: %f %f %f\n", u.x,u.y, u.z, v.x, v.y, v.z);
//	//printf("normal: %f %f %f\n", normal.x, normal.y, normal.z);
//	normals[index] = normal;
//	vertices[index] = a;
//	texCoords[index][0] = 0.0; texCoords[index][1] = 0.0;
//	index++;
//
//	normals[index] = normal;
//	vertices[index] = b;
//	texCoords[index][0] = 0.0; texCoords[index][1] = 1.0;
//	index++;
//
//	normals[index] = normal;
//	vertices[index] = c;
//	texCoords[index][0] = 1.0; texCoords[index][1] = 1.0;
//	index++;
//
//
//	normals[index] = normal;
//	vertices[index] = d;
//	texCoords[index][0] = 1.0; texCoords[index][1] = 0.0;
//	index++;
//}
//
//void SimpleModel::DivideFace(const Vec3& a, const Vec3& b, const Vec3& c, const Vec3& d, int count)
//{
//	if (count > 0){
//		Vec3 v1 = glm::normalize(a + b);
//		Vec3 v2 = glm::normalize(b + c);
//		Vec3 v3 = glm::normalize(c + d);
//		Vec3 v4 = glm::normalize(d + a);
//		Vec3 vc = glm::normalize(a + c);
//		DivideFace(a, v1, vc, v4, count - 1);
//		DivideFace(v1, b, v2, vc, count - 1);
//		DivideFace(vc, v2, c, v3, count - 1);
//		DivideFace(v4, vc, v3, d, count - 1);
//	}
//	else{
//		LoadFace(a, b, c, d);
//	}
//}
//
//void SimpleModel::SphericalNormals()
//{
//	for (int j = 0; j < numVertices; ++j){
//		normals[j] = glm::normalize(vertices[j]);
//	}
//}