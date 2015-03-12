#include "Engine.h"
#include "SimpleModel.h"
#include "QuadSphere.h"
#include "ShaderManager.h"
#include "Game.h"
#include "RMatrix.h"
#include "Assets.h"

using namespace rb;
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
	ShaderManager::LoadShader("refract.vert", "refract.frag", Shader::Refract);
	ShaderManager::LoadShader("fresnel.vert", "fresnel.frag", Shader::Fresnel);

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
	glUniformMatrix4fv(shader->GetStdUniformLoc(Shader::ModelMatrix), 1, GL_FALSE, RMatrix::ValuePtr(testObj->GetTransform()));
	glUniformMatrix4fv(shader->GetStdUniformLoc(Shader::ViewMatrix), 1, GL_FALSE, RMatrix::ValuePtr(camera->View()));
	glUniformMatrix4fv(shader->GetStdUniformLoc(Shader::ProjectionMatrix), 1, GL_FALSE, RMatrix::ValuePtr(camera->Projection()));
	glUniform3f(glGetUniformLocation(shader->Program(), "uViewPos"), camera->Position().x, camera->Position().y, camera->Position().z);
	glUniform1i(glGetUniformLocation(shader->Program(), "uCubeMap"), 0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, skybox->GetTexture().texID);
	model->Render();
	glUseProgram(0);
	///temp for reflective

	//renderer->RenderGameObject(testObj, camera);
	renderer->PostRender();
}

void Engine::SetupScene()
{

	camera = new Camera(glm::vec3(0.0f, 1.0f, 5.0f));
	camera->SetProjection(53.13f, (float)windowWidth / (float)windowHeight, 0.1f, 100.0f);

	skybox = new Skybox();

	light = Light(glm::vec3(-4.0f, 1.0f, 4.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f), glm::vec3(1.0f));
	renderer->SetLight(light);

	//SimpleModel* cubeModel = new SimpleModel(PrimitiveType::Cube,
	//	ShaderManager::GetShader(Shader::Lit_Untextured),
	//	Material(glm::vec3(.7f, 0.7f, 0.7f), glm::vec3(1.0f, 1.0f, 1.0f), 128.0f));

	//TextureManager::LoadTexture("Crate", "wooden crate.jpg", Texture::Diffuse);
	////TextureManager::LoadTexture("Crate", "de.tga");

	//SimpleModel* textureCubeModel = new SimpleModel(PrimitiveType::Cube,
	//	ShaderManager::GetShader(Shader::Lit_Textured),
	//	Material(TextureManager::GetTexture("Crate")));

	//SimpleModel* sphereModel = new SimpleModel(PrimitiveType::Sphere,
	//	ShaderManager::GetShader(Shader::Lit_Untextured),
	//	Material(glm::vec3(.7f, 0.7f, 0.7f), glm::vec3(1.0f, 1.0f, 1.0f), 128.0f));

	//SimpleModel* quadSphere = new SimpleModel(PrimitiveType::QuadSphere,
	//	ShaderManager::GetShader(Shader::Lit_Untextured),
	//	Material(glm::vec3(.7f, 0.7f, 0.7f), glm::vec3(1.0f, 1.0f, 1.0f), 128.0f));

	//SimpleModel* reflectCube = new SimpleModel(PrimitiveType::Cube,
	//	ShaderManager::GetShader(Shader::Reflective),
	//	Material());

	//Model* testModel = new Model("Sphere Model/sphere.obj",
	//	//Material(TextureManager::GetTexture("Crate")),
	//	ShaderManager::GetShader(Shader::Lit_Textured));

	/*Model* reflectSphere = new Model("Sphere Model/sphere.obj",
		ShaderManager::GetShader(Shader::Fresnel));
	testObj = new GameObject(reflectSphere);*/

	/*Model* nanosuit = new Model("nanosuit/nanosuit.obj",
		ShaderManager::GetShader(Shader::Reflective));
	testObj = new GameObject(nanosuit, Vec3(0.0f, -2.0f, 0.0f), Mat4(1.0f), Vec3(0.25f));*/

	Model* ship = new Model("SmallShip/shipA_OBJ.obj",
		ShaderManager::GetShader(Shader::Refract));
	testObj = new GameObject(ship, Vec3(0.0f), RMatrix::Rotate(120.0f, RVector::up),Vec3(0.03f));
	
	//testObj = new GameObject(shipModel);
	//testObj = new GameObject(reflectShip);
	//testObj->scale = Vec3(0.05f);
	//testObj = new GameObject(diamond);
	//testObj->scale = Vec3(0.005f);

	//testObj = new GameObject(reflectSphere);
	
	//testObj = new GameObject(testModel);
	//testObj = new GameObject(reflectCube);
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
