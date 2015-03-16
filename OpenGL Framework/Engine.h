#ifndef R_ENGINE_H_
#define R_ENGINE_H_

#include "Renderer.h"
#include "Input.h"
#include "GameObject.h"
#include "Light.h"
#include "TextureManager.h"
#include <functional>
#include "Skybox.h"
namespace rb
{
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
		const int windowWidth = 1440;
		const int windowHeight = 1000;
		const float dt = 0.16f;

		double lastTime = 0.0f;
		float cameraDistance = 8.0f;
		float camSpeed = .03f;
		class Game* game;
		//Engine components
		Renderer* renderer;
		Input* input;

		//Scene objects
		GameObject* testObj;
		Camera* camera;
		Light light;
		Skybox* skybox;
		void SetupScene();
	};
}
#endif // !R_ENGINE_H_
