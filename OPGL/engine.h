// C/C++ Standard Libraries
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

// OpenGL Related Libraries
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

class Engine {
	GLFWwindow *m_window;

public:
	Engine();
	int initialize();
	void loop();
};
