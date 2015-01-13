#ifndef OPGL_ENGINE_H
#define OPGL_ENGINE_H 1

// C/C++ Standard Libraries
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

// OpenGL
#include "opengl.h"

// Program Includes
#include "world.h"

class Engine {
	GLFWwindow *m_window;
	World *m_world;
	GLuint m_vao;
	glm::mat4 m_viewMatrix;
	glm::mat4 m_projectionMatrix;
	glm::mat4 m_viewProjectionMatrix;

public:
	Engine();
	~Engine();
	int initialize(int screenWidth, int screenHeight);
	void loop();
};

#endif