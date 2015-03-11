#pragma once
#include <map>
#include <glew.h>
#include <string>
#include "Shader.h"

typedef std::map<Shader::ShaderType, Shader*> ShaderTable;

class ShaderManager
{
public:
	static void LoadShader(const std::string& vertFileName, const std::string& fragFileName, Shader::ShaderType type);
	static Shader* GetShader(Shader::ShaderType type);
	static void Clear();

private:
	static ShaderTable shaderTable;

};

