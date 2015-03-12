#include "Engine.h"
#include "SimpleModel.h"
#include "QuadSphere.h"
#include "ShaderManager.h"
#include "Game.h"
#include <glm\gtc\type_ptr.hpp>

Engine::Engine()
{
	renderer = new Renderer(windowWidth, windowHeight, 0, 0, "OpenGL Framework");
	input = new Input(renderer->Window());
	//updateMethod = nullptr;
	ShaderManager::LoadShader("unlit_untextured_Shader.vert", "unlit_untextured_Shader.frag", Shader::Unlit_Untextured);
	ShaderManager::LoadShader("lit_untextured_Shader.vert", "lit_untextured_Shader.frag", Shader::Lit_Untextured);
	ShaderManager::LoadShader("lit_textured_Shader.vert", "lit_textured_Shader.frag", Shader::Lit_Textured);
	ShaderManager::LoadShader("skybox_Shader.vert", "skybox_Shader.frag", Shader::Skybox);
	ShaderManager::LoadShader("reflective.vert", "reflective.frag", Shader::Reflective);

	SetupScene();
}


Engine::~Engine()
{
	if (renderer)
	{
		delete renderer;
		renderer = nullptr;
	}
	if (input)
	{
		delete input;
		input = nullptr;
	}
}

void Engine::Run()
{
	//game loop
	while (!glfwWindowShouldClose(renderer->Window()))
	{
		glfwPollEvents();
		
		double now = glfwGetTime();
		double delta = now - lastTime;
		if (delta >= (double)dt)
		{
			//printf("delta: %d\n", delta);
			lastTime = now;
			Update(dt);
			if (game != nullptr)
			{
				game->Update(dt);
			}
		}
		Render();
	}

	glfwTerminate();
}

void  Engine::Update(float dt)
{
	if (Input::GetKeyDown(GLFW_KEY_ESCAPE))
	{
		glfwSetWindowShouldClose(renderer->Window(), GL_TRUE);
	}
	//printf("Mouse delta: (%f, %f)\n", Input::MouseDelta().x, Input::MouseDelta().y);
	camera->RotateCamera(Input::MouseDelta().x, glm::vec3(0.0f, -1.0f, 0.0f));
	camera->RotateCamera(Input::MouseDelta().y, glm::vec3(1.0f, 0.0f, 0.0f));

	Input::Update();

	//updateMethod();
	//sphere->position += glm::vec3(.5f, 0.0f, 0.0f)*dt;

	//printf("Update\n");
}

void Engine::Render()
{
	renderer->PreRender();
	//camera->RotateCamera(.3f, glm::vec3(0.0f, 1.0f, 0.0f));

	//SKYBOX
	glDepthMask(GL_FALSE);
	
	skybox->Render(camera);
	glDepthMask(GL_TRUE);
	glUseProgram(0);
	//SKYBOX

	//temp for reflective
	Model* model = testObj->GetModel();
	Shader* shader = model->shader;
	shader->Use();
	glUniformMatrix4fv(shader->GetStdUniformLoc(Shader::ModelMatrix), 1, GL_FALSE, glm::value_ptr(testObj->GetTransform()));
	glUniformMatrix4fv(shader->GetStdUniformLoc(Shader::ViewMatrix), 1, GL_FALSE, glm::value_ptr(camera->View()));
	glUniformMatrix4fv(shader->GetStdUniformLoc(Shader::ProjectionMatrix), 1, GL_FALSE, glm::value_ptr(camera->Projection()));
	glUniform3f(glGetUniformLocation(shader->Program(), "uViewPos"), camera->Position().x, camera->Position().y, camera->Position().z);
	glUniform1i(glGetUniformLocation(shader->Program(), "uCubeMap"), 0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, skybox->TextureID());
	model->Render();
	glUseProgram(0);
	///temp for reflective

	//renderer->RenderGameObject(testObj, camera);
	//quadSphere->Render(camera);
	renderer->PostRender();
}

void Engine::SetupScene()
{

	camera = new Camera(glm::vec3(0.0f, 1.0f, 5.0f));
	camera->SetProjection(53.13f, (float)windowWidth / (float)windowHeight, 0.1f, 100.0f);

	skybox = new Skybox();
	
	light = Light(glm::vec3(-4.0f,1.0f,4.0f), glm::vec3(1.0f,1.0f,0.0f), glm::vec3(1.0f), glm::vec3(1.0f));
	renderer->SetLight(light);

	SimpleModel* cubeModel = new SimpleModel(PrimitiveType::Cube, 
		ShaderManager::GetShader(Shader::Lit_Untextured), 
		Material(glm::vec3(.7f, 0.7f, 0.7f), glm::vec3(1.0f, 1.0f, 1.0f), 128.0f));

	TextureManager::LoadTexture("Crate", "wooden crate.jpg");
	//TextureManager::LoadTexture("Crate", "de.tga");
	
	SimpleModel* textureCubeModel = new SimpleModel(PrimitiveType::Cube,
		ShaderManager::GetShader(Shader::Lit_Textured),
		Material(TextureManager::GetTexture("Crate")));
	
	SimpleModel* sphereModel = new SimpleModel(PrimitiveType::Sphere, 
		ShaderManager::GetShader(Shader::Lit_Untextured),
		Material(glm::vec3(.7f, 0.7f, 0.7f), glm::vec3(1.0f, 1.0f, 1.0f), 128.0f));

	SimpleModel* quadSphere = new SimpleModel(PrimitiveType::QuadSphere,
		ShaderManager::GetShader(Shader::Lit_Untextured),
		Material(glm::vec3(.7f, 0.7f, 0.7f), glm::vec3(1.0f, 1.0f, 1.0f), 128.0f));

	SimpleModel* reflectCube = new SimpleModel(PrimitiveType::Cube,
		ShaderManager::GetShader(Shader::Reflective),
		NULL);

	//QuadSphere* quadSphere = new QuadSphere(4, ShaderManager::GetShader(Lit_Untextured), Material(glm::vec3(.7f, 0.7f, 0.7f), glm::vec3(1.0f, 1.0f, 1.0f), 128.0f));

	//////////
	//quadSphere = new QuadSphere(4, nullptr, Material(glm::vec3(.7f, 0.7f, 0.7f), glm::vec3(1.0f, 1.0f, 1.0f), 128.0f));
	///////////////

	testObj = new GameObject(reflectCube);
	//testObj = new GameObject(textureCubeModel);
	//testObj = new GameObject(cubeModel);
	//sphere = new GameObject(quadSphere);
	//sphere = new GameObject(sphereModel);

	/*sphere = new GameObject(new SimpleModel(
		PrimitiveType::Sphere, 
		ShaderManager::GetShader(Lit_Untextured),
		Material(glm::vec3(.7f,0.7f,0.7f),glm::vec3(1.0f,1.0f,1.0f),128.0f)));*/
}

void Engine::RegisterGame(class Game* game)
{
	this->game = game;
}

//void Engine::RegisterUpdateCallback(UpdateMethod updateMethod, Game* game)
//{
//	printf("register callback\n");
//	this->updateMethod = std::bind(updateMethod, game, std::placeholders::_1);
//	//this->updateMethod = updateMethod;
//}
