#pragma once
#include <glfw3.h>
#include <glm/glm.hpp>
#include <functional>

class Input
{
public:
	Input(GLFWwindow* window);
	~Input();

	static void Update();
	static bool GetKeyDown(int key);
	static glm::vec2 MouseDelta();
	static glm::vec2 MousePosition();

private:
	
	static bool* keyStates;
	static bool mouseActive;
	static float sensitivity;
	static glm::vec2 lastMousePos, currentMousePos, mouseDelta;

	static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
	static void MouseCallback(GLFWwindow* window, double xPos, double yPos);
};

