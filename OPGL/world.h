#ifndef OPGL_WORLD_H
#define OPGL_WORLD_H 1

// C/C++ Standard Libraries
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

// OpenGL
#include "opengl.h"

// Program Includes
#include "shader.h"

class World {
	std::vector<GLfloat> m_vertices;
	GLuint m_vao;
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