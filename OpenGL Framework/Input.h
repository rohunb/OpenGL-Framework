#ifndef R_INPUT_H_
#define R_INPUT_H_

#include <glfw3.h>
#include <functional>
#include "RVector.h"
namespace rb
{
	class Input
	{
	public:
		Input(GLFWwindow* window);
		~Input();
		static void Update();
		static bool GetKeyDown(int key);
		static Vec2 MouseDelta();
		static Vec2 MousePosition();

	private:

		static bool* keyStates;
		static bool mouseActive;
		static float sensitivity;
		static Vec2 lastMousePos, currentMousePos, mouseDelta;

		static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
		static void MouseCallback(GLFWwindow* window, double xPos, double yPos);
		static void MouseClickCallback(GLFWwindow* window, int button, int action, int mods);
	};
}
#endif // !R_INPUT_H_
