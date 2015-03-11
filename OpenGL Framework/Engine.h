#pragma once
#include "Renderer.h"
#include "Input.h"
#include "GameObject.h"
#include "Light.h"
#include "TextureManager.h"
#include <functional>
#include "Skybox.h"

class Engine
{
public:
	Engine();
	~Engine();

	void Run();
	void Render();

	void Update(float dt);
	void RegisterGame(class Game* game);
	/*typedef std::function<void(float)> UpdateMethod;
	void RegisterUpdateCallback(UpdateMethod updateMethod, class Game* object);
	UpdateMethod updateMethod;*/

private:


	const int windowWidth = 1024;
	const int windowHeight = 768;

	const float dt = 0.16f;
	double lastTime=0.0f;

	class Game* game;
	//Engine components
	Renderer* renderer;
	Input* input;

	GameObject* testObj;
	Camera* camera;
	Light light;
	Skybox* skybox;


	void SetupScene();
	
};

