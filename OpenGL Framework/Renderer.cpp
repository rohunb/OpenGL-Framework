#include "Renderer.h"
#include <glfw3.h>
#include <iostream>
#include "RMatrix.h"
#include "Shader.h"
#include "Debug.h"

using namespace rb;
Renderer::Renderer(int windowWidth, int windowHeight, int windowPosX, int windowPosY, char* windowName)
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	window = glfwCreateWindow(windowWidth, windowHeight, "OpenGL Framework", nullptr, nullptr);
	glfwMakeContextCurrent(window);
	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glewExperimental = GL_TRUE;
	int status = glewInit();
	std::cout << "Glew Init status: " << status << std::endl;

	glViewport(windowPosX, windowPosY, windowWidth, windowHeight);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
}


Renderer::~Renderer()
{
}



void Renderer::PreRender() const
{
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::PostRender() const
{
	glfwSwapBuffers(window);
	//glutSwapBuffers();

}

void Renderer::RenderGameObject(const GameObject* gameObject, const Camera* camera) 
{
	Model* model = gameObject->GetModel();
	Shader* shader = model->shader;
	shader->Use();
	glUniformMatrix4fv(shader->GetStdUniformLoc(Shader::StdUniform::ModelMatrix), 1, GL_FALSE, RMatrix::ValuePtr(gameObject->GetTransform()));
	//glUniformMatrix4fv(shader->GetStdUniformLoc(ModelMatrix), 1, GL_FALSE, glm::value_ptr(glm::mat4(1.0f)));
	glUniformMatrix4fv(shader->GetStdUniformLoc(Shader::StdUniform::ViewMatrix), 1, GL_FALSE, RMatrix::ValuePtr(camera->View()));
	glUniformMatrix4fv(shader->GetStdUniformLoc(Shader::StdUniform::ProjectionMatrix), 1, GL_FALSE, RMatrix::ValuePtr(camera->Projection()));
	
	glUniform3f(glGetUniformLocation(shader->Program(), "uViewPos"), camera->Position().x, camera->Position().y, camera->Position().z);
	
	//material
	switch (shader->Type())
	{
	case Shader::ShaderType::LitUntextured:
		glUniform3f(glGetUniformLocation(shader->Program(), "uMaterial.diffuse"), model->material.Diffuse().x, model->material.Diffuse().y, model->material.Diffuse().z);
		break;
	case Shader::ShaderType::LitTextured:
		glUniform1i(glGetUniformLocation(shader->Program(), "uMaterial.diffuseTexture"), 0);
		glBindTexture(GL_TEXTURE_2D, model->material.DiffuseTexture().texID);
		break;
	case Shader::ShaderType::ExplodeUnlit:
		glUniform1i(glGetUniformLocation(shader->Program(), "diffuseTexture"), 0);
		glBindTexture(GL_TEXTURE_2D, model->material.DiffuseTexture().texID);
		glUniform1f(glGetUniformLocation(shader->Program(), "uTime"), static_cast<float>(glfwGetTime()));
		glUniform1f(glGetUniformLocation(shader->Program(), "uExplodeMag"),1.0f);
		break;
	default:
		break;
	}

	glUniform3f(glGetUniformLocation(shader->Program(), "uMaterial.specular"), model->material.Specular().x, model->material.Specular().y, model->material.Specular().z);
	glUniform1f(glGetUniformLocation(shader->Program(), "uMaterial.shininess"), model->material.Shininess());
	//light
	glUniform3f(glGetUniformLocation(shader->Program(), "uLight.position"), light.position.x, light.position.y, light.position.z);
	glUniform3f(glGetUniformLocation(shader->Program(), "uLight.ambient"), light.ambient.x, light.ambient.y, light.ambient.z);
	glUniform3f(glGetUniformLocation(shader->Program(), "uLight.diffuse"), light.diffuse.x, light.diffuse.y, light.diffuse.z);
	glUniform3f(glGetUniformLocation(shader->Program(), "uLight.specular"), light.specular.x, light.specular.y, light.specular.z);


	model->Render();
	glUseProgram(0);
}

void Renderer::SetLight(Light light)
{
	this->light = light;
}
