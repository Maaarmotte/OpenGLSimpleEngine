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
#include "texture.h"

class World {
	std::vector<GLfloat> m_vertices;
	std::vector<GLuint> m_indices;
	GLuint m_vao;
	GLuint m_vertexbuffer;
	GLuint m_indexBuffer;
	glm::mat4 m_modelMatrix;
	Shader m_shader;
	Texture m_texture;

public:
	World();
	void load();
	void updateVertices(const unsigned int size, const GLfloat *vertices, const unsigned int sizeIndices, const GLuint *indices);
	void draw(glm::mat4& projectionViewMatrix) const;
};

#endif