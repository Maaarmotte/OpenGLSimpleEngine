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
	std::vector<GLfloat> m_vertices;
	GLuint m_vertexbuffer;
	Shader *m_shader;
	glm::mat4 m_modelMatrix;

public:
	~World();
	void initialize();
	void updateVertices(const unsigned int size, const GLfloat *vertices);
	void draw(glm::mat4& projectionViewMatrix) const;
};

#endif