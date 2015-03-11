#pragma once
#include <glew.h>
#include <map>
#include <string>

typedef std::map<std::string, GLuint> TextureTable;

class TextureManager
{
public:
	static void LoadTexture(const std::string& name, const std::string& path);
	static void LoadTextures(int numAttributes);
	static GLuint GetTexture(const std::string& name);
	static void Clear();

private:
	static TextureTable textureTable;
	static GLuint LoadFromFile(const std::string& path);
};

