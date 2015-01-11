#include "world.h"

World::~World() {
	delete m_shader;
}

void World::initialize() {
	m_modelMatrix = glm::mat4(1.0f);
	m_shader = new Shader();
	m_shader->loadFromFile("world_vert.glsl", "world_frag.glsl");
	m_shader->compile();
	glGenBuffers(1, &m_vertexbuffer);												// Instantiate a new vertex buffer
}

void World::updateVertices(const unsigned int size, const GLfloat *vertices) {
	m_vertices.reserve(size);
	m_vertices.insert(m_vertices.end(), vertices, vertices+size);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexbuffer);															// Bind the vertex buffer
	glBufferData(GL_ARRAY_BUFFER, m_vertices.size()*sizeof(m_vertices[0]), &m_vertices[0], GL_STATIC_DRAW);	// and fill it with vertices
}

void World::draw(glm::mat4& projectionViewMatrix) const {
	m_shader->activate();

	GLint position = glGetAttribLocation(m_shader->getProgramID(), "position");
	GLuint matrix = glGetUniformLocation(m_shader->getProgramID(), "MVP");
	glm::mat4 mvp = projectionViewMatrix*m_modelMatrix;

	glEnableVertexAttribArray(position);
	glUniformMatrix4fv(matrix, 1, GL_FALSE, &mvp[0][0]);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexbuffer);
	glVertexAttribPointer(position, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glDrawArrays(GL_TRIANGLES, 0, 3);												// Starting from vertex 0; 3 vertices total -> 1 triangle
	glDisableVertexAttribArray(position);
}