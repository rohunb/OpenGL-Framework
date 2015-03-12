#include "Renderer.h"
#include <glfw3.h>
#include <iostream>
#include "RMatrix.h"
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

	/*glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(windowWidth, windowHeight);
	glutInitWindowPosition(windowPosX, windowPosY);
	glutCreateWindow(windowName);*/

	glewExperimental = GL_TRUE;
	int status = glewInit();
	std::cout << "Glew Init status: " << status << std::endl;

	glViewport(windowPosX, windowPosY, windowWidth, windowHeight);

	glEnable(GL_DEPTH_TEST);

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

void Renderer::RenderGameObject(const GameObject* gameObject, const Camera* camera) const
{
	Model* model = gameObject->GetModel();
	Shader* shader = model->shader;
	shader->Use();
	glUniformMatrix4fv(shader->GetStdUniformLoc(Shader::ModelMatrix), 1, GL_FALSE, RMatrix::ValuePtr(gameObject->GetTransform()));
	//glUniformMatrix4fv(shader->GetStdUniformLoc(ModelMatrix), 1, GL_FALSE, glm::value_ptr(glm::mat4(1.0f)));
	glUniformMatrix4fv(shader->GetStdUniformLoc(Shader::ViewMatrix), 1, GL_FALSE, RMatrix::ValuePtr(camera->View()));
	glUniformMatrix4fv(shader->GetStdUniformLoc(Shader::ProjectionMatrix), 1, GL_FALSE, RMatrix::ValuePtr(camera->Projection()));
	
	glUniform3f(glGetUniformLocation(shader->Program(), "uViewPos"), camera->Position().x, camera->Position().y, camera->Position().z);

	//material
	if (shader->Type() == Shader::ShaderType::Lit_Untextured)
	{
		glUniform3f(glGetUniformLocation(shader->Program(), "uMaterial.diffuse"), model->material.diffuse.x, model->material.diffuse.y, model->material.diffuse.z);
	}
	else if (shader->Type() == Shader::ShaderType::Lit_Textured)
	{
		glUniform1i(glGetUniformLocation(shader->Program(), "uMaterial.texture_diffuse1"), 0);
		glBindTexture(GL_TEXTURE_2D, model->material.diffuseTextureID);
	}
	glUniform3f(glGetUniformLocation(shader->Program(), "uMaterial.specular"), model->material.specular.x, model->material.specular.y, model->material.specular.z);
	glUniform1f(glGetUniformLocation(shader->Program(), "uMaterial.shininess"), model->material.shininess);
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
