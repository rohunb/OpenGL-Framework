#include "TextureManager.h"
#include <iostream>
#include <SOIL.h>
#include "Assets.h"

using namespace rb;
TextureTable TextureManager::textureTable;

void TextureManager::LoadTexture(const std::string& name, const std::string& path)
{
	if (textureTable.find(name) == textureTable.end())
	{
		textureTable[name] = LoadFromFile(Assets::texturesPath + path);
	}
	else
	{
		std::cerr << "Texture " << name << " already exists in manager\n";
	}
}

void TextureManager::LoadTextures(int numAttributes)
{

}

GLuint TextureManager::GetTexture(const std::string& name)
{
	if (textureTable.find(name) == textureTable.end())
	{
		std::cerr << "Texture " << name << " not found in Manager\n";
		return 0;
	}
	else
	{
		return textureTable[name];
	}
}

void TextureManager::Clear()
{

}

GLuint TextureManager::LoadFromFile(const std::string& path)
{
	
	int width, height;
	int channels = 0;
	unsigned char* image = SOIL_load_image(path.c_str(), &width, &height, &channels, SOIL_LOAD_RGB);

	GLuint textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	glBindTexture(GL_TEXTURE_2D, 0);
	SOIL_free_image_data(image);

	std::cout << "Loaded texture from " << path << " and bound to ID " << textureID << std::endl;

	return textureID;
}
