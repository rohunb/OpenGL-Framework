#include "ShaderManager.h"
#include <iostream>
#include "Assets.h"

ShaderTable ShaderManager::shaderTable;

void ShaderManager::LoadShader(const std::string& vertFileName, const std::string& fragFileName, Shader::ShaderType type)
{
	if (shaderTable.find(type) == shaderTable.end())
	{
		shaderTable[type] = new Shader((Assets::shadersPath + vertFileName).c_str(),(Assets::shadersPath+ fragFileName).c_str(), type);
	}
	else
	{
		std::cout << "Shader " << vertFileName << "already exists in manager\n";
	}
}

Shader* ShaderManager::GetShader(Shader::ShaderType type)
{
	if (shaderTable.find(type) == shaderTable.end())
	{
		std::cout << "Shader does not exist in manager\n";
		return nullptr;
	}
	else
	{
		return shaderTable[type];
	}
}

void ShaderManager::Clear()
{
	for (auto iter: shaderTable)
	{
		delete iter.second;
	}
	shaderTable.clear();
}
