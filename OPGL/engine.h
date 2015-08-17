#ifndef OPGL_ENGINE_H
#define OPGL_ENGINE_H 1

// C/C++ Standard Libraries
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#define _USE_MATH_DEFINES
#include <math.h>

// OpenGL
#include "opengl.h"

// Program Includes
#include "world.h"
#include "camera.h"

class Engine {
	GLFWwindow *m_window;
	World m_world;
	Camera m_camera;
	GLdouble m_drawTime;

public:
	Engine(int screenWidth, int screenHeight);
	void loop();
};

#endif