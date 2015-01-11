#include "world.h"

void World::initialize() {
	m_vertices = new GLfloat[9] { -1.0f, -1.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f };
	m_shader = new Shader();
	m_shader->loadFromFile("world_vert.glsl", "world_frag.glsl");
	m_shader->compile();
	glGenBuffers(1, &m_vertexbuffer);												// Instantiate a new vertex buffer
}

void World::updateVertices() {
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexbuffer);									// Bind the vertex buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*9, m_vertices, GL_STATIC_DRAW);	// and fill it with vertices
}

void World::draw() const {
	m_shader->activate();
	GLint position = glGetAttribLocation(m_shader->getProgramID(), "position");
	glEnableVertexAttribArray(position);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexbuffer);
	glVertexAttribPointer(position, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glDrawArrays(GL_TRIANGLES, 0, 3);												// Starting from vertex 0; 3 vertices total -> 1 triangle
	glDisableVertexAttribArray(position);
}