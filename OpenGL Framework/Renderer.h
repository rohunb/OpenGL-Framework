#ifndef R_RENDERER_H_
#define R_RENDERER_H_

#define GLEW_STATIC
#include <glew.h>
#include "glfw3.h"
#include "Camera.h"
#include "GameObject.h"
#include "Light.h"

namespace rb
{
	class Renderer
	{
	public:

		GLFWwindow* Window() const { return window; }
		Renderer(int windowWidth, int windowHeight, int windowPosX, int windowPosY, char* windowName);
		~Renderer();

		void PreRender() const;
		void PostRender() const;
		void RenderGameObject(const GameObject* gameObject, const Camera* camera) const;
		void SetLight(Light light);

	private:
		GLFWwindow* window;
		Light light;

	};
}
#endif // !R_RENDERER_H_


