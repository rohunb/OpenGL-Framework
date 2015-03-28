#ifndef R_SHADER_H_
#define R_SHADER_H_
#define GLEW_STATIC
#include "glew.h"
#include "RString.h"
namespace rb
{
	class Shader
	{
	public:
		enum class ShaderType { Unlit_Untextured, Lit_Untextured, Three_Lit_Untextured, Lit_Textured, Skybox, Reflective, Refract, Fresnel };
		enum class StdUniform { ModelMatrix, ViewMatrix, ProjectionMatrix };
		enum class StdAttrib { VertexAttrib, NormalAttrib, TexCoordAttrib, ColourAttrib };

		inline GLuint Program() const { return program; }
		inline ShaderType Type() const { return type; }
		Shader(const string& vertFileName, const string& fragFileName, ShaderType type);
		Shader(const string& vertFileName, const string& fragFileName, const string& geomFileName, ShaderType type);
		~Shader();
		void Use();
		GLuint GetStdUniformLoc(StdUniform uniform);
		void HandleStdUniforms(const char* modelMatrixName, const char* viewMatrixName, const char* projMatrixName);

	private:
		ShaderType type;
		GLuint program, vertShader, fragShader;
		GLuint stdUniformLoc[sizeof(StdUniform)];

		char* ReadTextFile(const char* fileName);
		void ProcessShader(const char* vertFileName, const char* fragFileName);
		void Link();
	};
}
#endif // !R_SHADER_H_


