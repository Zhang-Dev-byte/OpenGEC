#pragma once
#include "Opengl.h"
class Application {
public:
	static void HandleInput(GLFWwindow* window);
	static void Update();
	static void Start();
};