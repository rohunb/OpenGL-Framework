#include "Input.h"

bool* Input::keyStates = new bool[1024];
bool Input::mouseActive = false;
float Input::sensitivity=0.5f;
glm::vec2 Input::lastMousePos = glm::vec2(0.0f);
glm::vec2 Input::currentMousePos = glm::vec2(0.0f);
glm::vec2 Input::mouseDelta = glm::vec2(0.0f);

Input::Input(GLFWwindow* window)
{
	for (int i = 0; i < 1024; i++)
	{
		keyStates[i] = false;
	}
	glfwSetKeyCallback(window, KeyCallback);
	glfwSetCursorPosCallback(window, MouseCallback);
}


Input::~Input()
{
	delete[] keyStates;
}

void Input::Update()
{
	mouseDelta.x = 0.0f;
	mouseDelta.y = 0.0f;
}

bool Input::GetKeyDown(int key)
{
	return keyStates[key];
}

glm::vec2 Input::MouseDelta()
{
	return mouseDelta;
}
glm::vec2 Input::MousePosition()
{
	return lastMousePos;
}

void Input::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (action == GLFW_PRESS)
	{
		keyStates[key] = true;
	}
	else if (action == GLFW_RELEASE)
	{
		keyStates[key] = false;
	}
}

void Input::MouseCallback(GLFWwindow* window, double xPos, double yPos)
{
	if (!mouseActive)
	{
		lastMousePos.x = xPos;
		lastMousePos.y = yPos;
		mouseActive = true;
	}
	mouseDelta.x = xPos - lastMousePos.x;
	mouseDelta.y = lastMousePos.y - yPos;
	mouseDelta.x *= sensitivity;
	mouseDelta.y *= sensitivity;
	lastMousePos.x = xPos;
	lastMousePos.y = yPos;
}
