#pragma once
#include <glm\glm.hpp>
#include <glew.h>

struct Material
{
	glm::vec3 diffuse;
	GLuint diffuseTextureID;
	glm::vec3 specular;
	float shininess;

	Material()
		:diffuse(glm::vec3(1.0f)),
		diffuseTextureID(0),
		specular(glm::vec3(1.0f)),
		shininess(4.0f)
	{}
	Material(const glm::vec3& _diffuseColour)
		:diffuse(_diffuseColour),
		diffuseTextureID(0),
		specular(glm::vec3(1.0f)),
		shininess(4.0f)
	{}
	Material(const glm::vec3& _diffuseColour, const glm::vec3& _specularColour, float _shininess)
		:diffuse(_diffuseColour),
		diffuseTextureID(0),
		specular(_specularColour),
		shininess(_shininess)
	{}
	Material(GLuint _diffuseTextureID, const glm::vec3& _specularColour, float _shininess)
		:diffuse(glm::vec3(1.0f)),
		diffuseTextureID(_diffuseTextureID),
		specular(_specularColour),
		shininess(_shininess)
	{}
	Material(GLuint _diffuseTextureID)
		:diffuseTextureID(_diffuseTextureID),
		diffuse(glm::vec3(1.0f)),
		specular(glm::vec3(1.0f)),
		shininess(4.0f)
	{}
	
};