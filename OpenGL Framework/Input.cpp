#include "Input.h"
using namespace rb;

bool* Input::keyStates = new bool[1024];
bool Input::mouseActive = false;
float Input::sensitivity=1.0f;
Vec2 Input::lastMousePos = Vec2(0.0f);
Vec2 Input::currentMousePos = Vec2(0.0f);
Vec2 Input::mouseDelta = Vec2(0.0f);

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

Vec2 Input::MouseDelta()
{
	return mouseDelta;
}
Vec2 Input::MousePosition()
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
		lastMousePos.x = (float)xPos;
		lastMousePos.y = (float)yPos;
		mouseActive = true;
	}
	mouseDelta.x = (float)xPos - lastMousePos.x;
	mouseDelta.y = lastMousePos.y - (float)yPos;
	mouseDelta.x *= sensitivity;
	mouseDelta.y *= sensitivity;
	lastMousePos.x = (float)xPos;
	lastMousePos.y = (float)yPos;
}
