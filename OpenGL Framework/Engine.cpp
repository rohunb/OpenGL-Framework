#include "Engine.h"
#include "SimpleModel.h"
#include "QuadSphere.h"
#include "ShaderManager.h"
#include "Game.h"
#include "RMatrix.h"
#include "Assets.h"
#include "Debug.h"
#include "ParticleSystem.h"

using namespace rb;
Engine::Engine()
{
	renderer = new Renderer(windowWidth, windowHeight, 0, 0, "OpenGL Framework");
	input = new Input(renderer->Window());
	//updateMethod = nullptr;
	ShaderManager::LoadShader("unlit_untextured_Shader.vert", "unlit_untextured_Shader.frag", Shader::ShaderType::UnlitUntextured);
	ShaderManager::LoadShader("lit_untextured_Shader.vert", "lit_untextured_Shader.frag", Shader::ShaderType::LitUntextured);
	ShaderManager::LoadShader("lit_textured_Shader.vert", "lit_textured_Shader.frag", Shader::ShaderType::LitTextured);
	ShaderManager::LoadShader("skybox_Shader.vert", "skybox_Shader.frag", Shader::ShaderType::Skybox);
	ShaderManager::LoadShader("reflective.vert", "reflective.frag", Shader::ShaderType::Reflective);
	ShaderManager::LoadShader("refract.vert", "refract.frag", Shader::ShaderType::Refract);
	ShaderManager::LoadShader("fresnel.vert", "fresnel.frag", Shader::ShaderType::Fresnel);
	ShaderManager::LoadShader("explode_unlit_textured.vert", "explode_unlit_textured.frag", "explode_unlit_textured.geom", Shader::ShaderType::ExplodeUnlit);
	ShaderManager::LoadShader("display_normals.vert", "display_normals.frag", "display_normals.geom", Shader::ShaderType::DisplayNormals);
	ShaderManager::LoadShader("particle_shader.vert", "particle_shader.frag", Shader::ShaderType::Particle);
	ShaderManager::LoadShader("particles_billboarded.vert", "particles_billboarded.frag", "particles_billboarded.geom", Shader::ShaderType::BillboardedParticle);

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
		//if (delta >= (double)dt)
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
	/*camera->RotateCamera(Input::MouseDelta().x, glm::vec3(0.0f, -1.0f, 0.0f));
	camera->RotateCamera(Input::MouseDelta().y, glm::vec3(1.0f, 0.0f, 0.0f));*/
	//Vec3 moveDir;
	if (Input::GetKeyDown(GLFW_KEY_A))
	{
		camera->Move(Camera::Left, camSpeed);
	}
	else if (Input::GetKeyDown(GLFW_KEY_D))
	{
		camera->Move(Camera::Right, camSpeed);
	}
	if (Input::GetKeyDown(GLFW_KEY_W))
	{
		camera->Move(Camera::Up, camSpeed);
	}
	else if (Input::GetKeyDown(GLFW_KEY_S))
	{
		camera->Move(Camera::Down, camSpeed);
	}
	camera->LookAt(testObj->position);
	float distance = glm::distance(camera->Position(), testObj->position);
	if (distance > cameraDistance)
	{
		float howFar = distance-cameraDistance;
		camera->Move(Camera::Forward, howFar);
	}
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
	/*Model* model = testObj->GetModel();
	Shader* shader = model->shader;
	shader->Use();
	glUniformMatrix4fv(shader->GetStdUniformLoc(Shader::ModelMatrix), 1, GL_FALSE, RMatrix::ValuePtr(testObj->GetTransform()));
	glUniformMatrix4fv(shader->GetStdUniformLoc(Shader::ViewMatrix), 1, GL_FALSE, RMatrix::ValuePtr(camera->View()));
	glUniformMatrix4fv(shader->GetStdUniformLoc(Shader::ProjectionMatrix), 1, GL_FALSE, RMatrix::ValuePtr(camera->Projection()));
	glUniform3f(glGetUniformLocation(shader->Program(), "uViewPos"), camera->Position().x, camera->Position().y, camera->Position().z);
	glUniform1i(glGetUniformLocation(shader->Program(), "uCubeMap"), 0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, skybox->GetTexture().texID);
	model->Render();
	glUseProgram(0);*/
	///temp for reflective
	//renderer->RenderGameObject(testObj, camera);
	
	particleSystem->Render(camera);
	//normal geom shader
	//////////////////////////////////////////////////////////////////////////
	//Shader* normalShader = ShaderManager::GetShader(Shader::ShaderType::DisplayNormals);
	//normalShader->Use();
	//glUniformMatrix4fv(normalShader->GetStdUniformLoc(Shader::StdUniform::ModelMatrix), 1, GL_FALSE, RMatrix::ValuePtr(testObj->GetTransform()));
	////glUniformMatrix4fv(shader->GetStdUniformLoc(ModelMatrix), 1, GL_FALSE, glm::value_ptr(glm::mat4(1.0f)));
	//glUniformMatrix4fv(normalShader->GetStdUniformLoc(Shader::StdUniform::ViewMatrix), 1, GL_FALSE, RMatrix::ValuePtr(camera->View()));
	//glUniformMatrix4fv(normalShader->GetStdUniformLoc(Shader::StdUniform::ProjectionMatrix), 1, GL_FALSE, RMatrix::ValuePtr(camera->Projection()));
	//testObj->GetModel()->Render();
	//glUseProgram(0);
	//////////////////////////////////////////////////////////////////////////

	renderer->PostRender();
}

void Engine::SetupScene()
{

	camera = new Camera(glm::vec3(0.0f, 1.0f, cameraDistance));
	camera->SetProjection(53.13f, (float)windowWidth / (float)windowHeight, 0.1f, 100.0f);

	skybox = new Skybox();

	light = Light(glm::vec3(-4.0f, 1.0f, 4.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f), glm::vec3(1.0f));
	renderer->SetLight(light);
	Debug::Info("test " + std::string(__FILE__) + " line " + std::to_string(__LINE__));
	//SimpleModel* cubeModel = new SimpleModel(PrimitiveType::Cube,
	//	ShaderManager::GetShader(Shader::LitUntextured),
	//	Material(glm::vec3(.7f, 0.7f, 0.7f), glm::vec3(1.0f, 1.0f, 1.0f), 128.0f));

	TextureManager::LoadTexture("Crate", "wooden crate.jpg", Texture::TextureType::Diffuse);
	////TextureManager::LoadTexture("Crate", "de.tga");

	//SimpleModel* textureCubeModel = new SimpleModel(PrimitiveType::Cube,
	//	ShaderManager::GetShader(Shader::Lit_Textured),
	//	Material(TextureManager::GetTexture("Crate")));

	//SimpleModel* sphereModel = new SimpleModel(PrimitiveType::Sphere,
	//	ShaderManager::GetShader(Shader::LitUntextured),
	//	Material(glm::vec3(.7f, 0.7f, 0.7f), glm::vec3(1.0f, 1.0f, 1.0f), 128.0f));

	//SimpleModel* quadSphere = new SimpleModel(PrimitiveType::QuadSphere,
	//	ShaderManager::GetShader(Shader::LitUntextured),
	//	Material(glm::vec3(.7f, 0.7f, 0.7f), glm::vec3(1.0f, 1.0f, 1.0f), 128.0f));

	//SimpleModel* reflectCube = new SimpleModel(PrimitiveType::Cube,
	//	ShaderManager::GetShader(Shader::Reflective),
	//	Material());

	/*Model* testModel = new Model("Sphere Model/sphere.obj",
		Material(TextureManager::GetTexture("Crate")),
		ShaderManager::GetShader(Shader::ShaderType::LitTextured));
	testObj = new GameObject(testModel);*/

	/*Model* reflectSphere = new Model("Sphere Model/sphere.obj",
		ShaderManager::GetShader(Shader::Fresnel));
	testObj = new GameObject(reflectSphere);*/

	/*Model* nanosuit = new Model("nanosuit/nanosuit.obj",
		ShaderManager::GetShader(Shader::Refract));
	testObj = new GameObject(nanosuit, Vec3(0.0f, 0.0f, 0.0f), Mat4(1.0f), Vec3(0.2f));*/
	
	TextureManager::LoadTexture("SmallShip", "small_ship.tga", Texture::TextureType::Diffuse);
	Model* ship = new Model("SmallShip/shipA_OBJ.obj",
		Material(TextureManager::GetTexture("SmallShip")),
		ShaderManager::GetShader(Shader::ShaderType::LitTextured));
	testObj = new GameObject(ship, Vec3(0.0f), RMatrix::Rotate(120.0f, RVector::up),Vec3(0.03f));
	
	//TextureManager::LoadTexture("Particle", "particle.png", Texture::TextureType::Diffuse);
	TextureManager::LoadTexture("Particle", "2201.jpg", Texture::TextureType::Diffuse);
	TextureManager::LoadTexture("Smiley", "smiley01.jpg", Texture::TextureType::Diffuse);
	
	particleSystem = new ParticleSystem(
		TextureManager::GetTexture("Particle"), 
		ShaderManager::GetShader(Shader::ShaderType::BillboardedParticle),
		500);


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
