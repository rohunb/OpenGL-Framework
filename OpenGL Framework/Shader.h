#pragma once
#define GLEW_STATIC
#include "glew.h"



class Shader
{
public:
	enum ShaderType { Unlit_Untextured, Lit_Untextured, Three_Lit_Untextured, Unlit_Textured, Lit_Textured, Skybox, Reflective };
	enum StdUniform { ModelMatrix, ViewMatrix, ProjectionMatrix };
	enum StdAttrib { VertexAttrib, NormalAttrib, TexCoordAttrib, ColourAttrib };

	inline GLuint Program() const { return program; }
	inline ShaderType Type() const { return type; }

	Shader(const char* vertFileName, const char* fragFileName, ShaderType type);
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

