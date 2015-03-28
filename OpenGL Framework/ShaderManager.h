#ifndef R_SHADER_MANAGER_H_
#define R_SHADER_MANAGER_H_

#include <map>
#include <glew.h>
#include "RString.h"
#include "Shader.h"

namespace rb
{
	using ShaderTable = std::map < Shader::ShaderType, Shader* > ;
	class ShaderManager
	{
	public:
		static void LoadShader(const std::string& vertFileName, const std::string& fragFileName, Shader::ShaderType type);
		static void LoadShader(const std::string& vertFileName, const std::string& fragFileName, const string& geomFileName, Shader::ShaderType type);
		static Shader* GetShader(Shader::ShaderType type);
		static void Clear();
	private:
		static ShaderTable shaderTable;
	};
}
#endif // !R_SHADER_MANAGER_H_


