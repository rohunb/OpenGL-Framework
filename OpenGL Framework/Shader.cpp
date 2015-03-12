#include "Shader.h"
#include <vector>
#include <fstream>

using uint = unsigned int;
using namespace rb;
Shader::Shader(const char* vertFileName, const char* fragFileName, ShaderType _type)
	:type(_type)
{
	ProcessShader(vertFileName, fragFileName);
	Link();
	HandleStdUniforms("uModel", "uView", "uProjection");
}

Shader::~Shader()
{
	glDetachShader(program, fragShader);
	glDetachShader(program, vertShader);
	glDeleteShader(fragShader);
	glDeleteShader(vertShader);
	glDeleteProgram(program);
}

void Shader::Use()
{
	glUseProgram(program);
}

GLuint Shader::GetStdUniformLoc(StdUniform uniform)
{
	return stdUniformLoc[uniform];
}

void Shader::HandleStdUniforms(const char* modelMatrixName, const char* viewMatrixName, const char* projMatrixName)
{
	std::vector<const char*> stdUniformNames = { modelMatrixName, viewMatrixName, projMatrixName };
	int count;
	glGetProgramiv(program, GL_ACTIVE_UNIFORMS, &count);
	printf("\nThere are %d active Uniforms\n", count);
	for (uint i = 0; i < stdUniformNames.size(); i++)
	{
		if (stdUniformNames[i] == NULL)
		{
			continue;
		}
		stdUniformLoc[i] = glGetUniformLocation(program, stdUniformNames[i]);
		if (stdUniformLoc[i] != -1)
		{
			printf("%s loc:%d\n", stdUniformNames[i], stdUniformLoc[i]);
		}
		else
		{
			printf("%s loc: unused\n", stdUniformNames[i]);
		}
	}
}

void Shader::ProcessShader(const char* vertFileName, const char* fragFileName)
{
	GLint status;
	program = vertShader = fragShader = 0;
	try
	{
		const char* vertText = ReadTextFile(vertFileName);
		const char* fragText = ReadTextFile(fragFileName);

		if (vertText == NULL || fragText == NULL)
		{
			return;
		}

		vertShader = glCreateShader(GL_VERTEX_SHADER);
		fragShader = glCreateShader(GL_FRAGMENT_SHADER);

		if (vertShader == 0 || fragShader == 0)
		{
			std::string errorMesg("Error creating shader");
			throw errorMesg;
		}

		glShaderSource(vertShader, 1, &vertText, 0);
		glShaderSource(fragShader, 1, &fragText, 0);

		glCompileShader(vertShader);
		glGetShaderiv(program, GL_COMPILE_STATUS, &status);
		if (status == 0)
		{
			GLsizei errorLogSize = 0;
			std::string errorLog;
			glGetShaderiv(program, GL_INFO_LOG_LENGTH, &errorLogSize);
			errorLog.resize(errorLogSize);
			glGetShaderInfoLog(program, errorLogSize, &errorLogSize, &errorLog[0]);
			throw errorLog;
		}
		glCompileShader(fragShader);
		glGetShaderiv(program, GL_COMPILE_STATUS, &status);
		if (status == 0) {
			GLsizei errorLogSize = 0;
			std::string errorLog;
			glGetShaderiv(program, GL_INFO_LOG_LENGTH, &errorLogSize);
			errorLog.resize(errorLogSize);
			glGetShaderInfoLog(program, errorLogSize, &errorLogSize, &errorLog[0]);
			throw errorLog;
		}

		program = glCreateProgram();
		glAttachShader(program, fragShader);
		glAttachShader(program, vertShader);

		if (vertText) delete[] vertText;
		if (fragText) delete[] fragText;
	}
	catch (std::string error)
	{
		printf("Shader Processing Error:%s\n", &error[0]);
	}
}

void Shader::Link()
{
	GLint status;
	try
	{
		glLinkProgram(program);
		glGetProgramiv(program, GL_LINK_STATUS, &status);
		if (status == 0)
		{
			GLsizei errorLogSize = 0;
			std::string errorLog;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &errorLogSize);
			errorLog.resize(errorLogSize);
			glGetShaderInfoLog(program, errorLogSize, &errorLogSize, &errorLog[0]);
			throw errorLog;
		}
	}
	catch (std::string error)
	{
		printf("Shader Linking Error:%s\n", &error[0]);
	}
}

char* Shader::ReadTextFile(const char* fileName)
{
	char* buffer = NULL;
	std::ifstream file(fileName, std::ios::binary);
	if (file.is_open())
	{
		file.seekg(0, std::ios::end);
		int bufferSize = (int)file.tellg();
		if (bufferSize == 0)
		{
			std::string errorMsg("Can't read shader file: ");
			errorMsg += std::string(fileName);
			throw errorMsg;
		}
		buffer = new char[(int)(bufferSize + 1)];
		file.seekg(0, std::ios::beg);
		file.read(buffer, bufferSize);
		buffer[bufferSize] = '\0';
		file.close();
	}
	else
	{
		std::string errorMsg("Can't open shader file: ");
		printf("ERROR:%s:%s\n", fileName, &errorMsg[0]);
	}
	return buffer;
}
