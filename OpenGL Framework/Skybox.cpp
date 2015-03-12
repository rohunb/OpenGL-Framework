#include "Skybox.h"
#include "TextureManager.h"
#include <vector>
#include <SOIL.h>
#include <iostream>

#include "ShaderManager.h"
#include "Camera.h"
// #include "glm\gtc\matrix_transform.hpp"
// #include "glm\gtc\type_ptr.hpp"
#include "Assets.h"
#include "RMatrix.h"
#include "Texture.h"

using namespace rb;
Skybox::Skybox(std::string textureName)
	:Skybox(TextureManager::GetTexture((textureName)))
{}

Skybox::Skybox(Texture _texture)
	: texture(_texture)
{
	Init();
}
Skybox::Skybox()
{
	Init();
}

Skybox::~Skybox()
{
	if (skyboxModel)
	{
		delete skyboxModel;
		skyboxModel = nullptr;
	}
}

void Skybox::Render(Camera* camera) const
{
	shader->Use();
	glBindVertexArray(VAO);
	//glUniformMatrix4fv(shader->GetStdUniformLoc(Shader::ViewMatrix), 1, GL_FALSE, glm::value_ptr(glm::lookAt(glm::vec3(0.0f), camera->LookPoint(), camera->Up())));
	glUniformMatrix4fv(shader->GetStdUniformLoc(Shader::ModelMatrix), 1, GL_FALSE, RMatrix::ValuePtr(RMatrix::Translate(camera->Position())));
	glUniformMatrix4fv(shader->GetStdUniformLoc(Shader::ViewMatrix), 1, GL_FALSE, RMatrix::ValuePtr(camera->View()));
	glUniformMatrix4fv(shader->GetStdUniformLoc(Shader::ProjectionMatrix), 1, GL_FALSE, RMatrix::ValuePtr(camera->Projection()));
	glUniform1i(glGetUniformLocation(shader->Program(), "uCubeMap"), 0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, texture.texID);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
	glBindVertexArray(0);

}
rb::Texture rb::Skybox::GetTexture() const
{
	return texture;
}

void Skybox::Init()
{

	
#pragma region SkyboxVertices

	GLfloat skyboxVertices[] = {
		// Positions          
		-1.0f, 1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, 1.0f, -1.0f,
		-1.0f, 1.0f, -1.0f,

		-1.0f, -1.0f, 1.0f,
		-1.0f, -1.0f, -1.0f,
		-1.0f, 1.0f, -1.0f,
		-1.0f, 1.0f, -1.0f,
		-1.0f, 1.0f, 1.0f,
		-1.0f, -1.0f, 1.0f,

		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,

		-1.0f, -1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, -1.0f, 1.0f,
		-1.0f, -1.0f, 1.0f,

		-1.0f, 1.0f, -1.0f,
		1.0f, 1.0f, -1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f, -1.0f,

		-1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f, 1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f, 1.0f,
		1.0f, -1.0f, 1.0f
	};
#pragma endregion// SkyboxVertices

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(Shader::VertexAttrib);
	glVertexAttribPointer(Shader::VertexAttrib, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glBindVertexArray(0);

	shader = ShaderManager::GetShader(Shader::Skybox);
	//shader->HandleStdUniforms()

	std::vector<std::string> faces{"hexagon_rt.jpg", "hexagon_lf.jpg", "hexagon_up.jpg", "hexagon_dn.jpg", "hexagon_bk.jpg", "hexagon_ft.jpg" };
	//std::vector<std::string> faces{ "desertsky_rt.jpg", "desertsky_lf.jpg", "desertsky_up.jpg", "desertsky_dn.jpg", "desertsky_bk.jpg", "desertsky_ft.jpg" };
	//std::vector<std::string> faces{ "posx.jpg", "negx.jpg", "posy.jpg", "negy.jpg", "posz.jpg", "negz.jpg" };
	glGenTextures(1, &texture.texID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, texture.texID);

	int width, height;
	unsigned char* image;

	for (GLuint i = 0; i < faces.size(); i++)
	{
		std::string path = Assets::skyboxesPath + "FierySky/" + faces[i];
		image = SOIL_load_image(path.c_str(), &width, &height, 0, SOIL_LOAD_RGB);
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
			0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
	
}

