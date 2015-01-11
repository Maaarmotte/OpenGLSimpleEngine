#ifndef OPGL_WORLD_H
#define OPGL_WORLD_H 1

// C/C++ Standard Libraries
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

// OpenGL Related Libraries
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

// Program Includes
#include "shader.h"

class World {
	GLfloat *m_vertices;
	GLuint m_vertexbuffer;
	Shader *m_shader;

public:
	void initialize();
	void updateVertices();
	void draw() const;
};

#endif