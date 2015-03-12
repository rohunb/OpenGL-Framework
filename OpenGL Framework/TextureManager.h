#pragma once
#include <glew.h>
#include <map>
#include "RString.h"
#include "Texture.h"
namespace rb
{
	using TextureTable = std::map <string, Texture>;
	class TextureManager
	{
	public:
		static void LoadTexture(const string& name, const string& path, Texture::TextureType texType);
		static void LoadTextureAbsPath(const string& name, const string& path, Texture::TextureType texType);
		static void LoadTextures(int numAttributes);
		static Texture GetTexture(const string& name);
		static void Clear();
	private:
		static TextureTable textureTable;
		static GLuint LoadFromFile(const string& path);
	};
}
