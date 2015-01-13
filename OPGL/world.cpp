#include "world.h"

World::~World() {
	delete m_shader;
}

void World::initialize() {
	m_modelMatrix = glm::mat4(1.0f);
	m_shader = new Shader();
	m_shader->addShaderFile(GL_VERTEX_SHADER, "world_vert.glsl");
	m_shader->addShaderFile(GL_FRAGMENT_SHADER, "world_frag.glsl");
	m_shader->link();

	glGenVertexArrays(1, &m_vao);		// Create a VAO so we don't need to specify where the vertices are everytime
	glBindVertexArray(m_vao);			// Bind it, we want to save to following data !
	glGenBuffers(1, &m_vertexbuffer);					// Instantiate a new vertex buffer
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexbuffer);		// And bind it

	GLint position = glGetAttribLocation(m_shader->getProgramID(), "position");
	glEnableVertexAttribArray(position);
	glVertexAttribPointer(position, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glBindVertexArray(0);
}

void World::updateVertices(const unsigned int size, const GLfloat *vertices) {
	m_vertices.reserve(size);
	m_vertices.insert(m_vertices.end(), vertices, vertices+size);

	glBindVertexArray(m_vao);		// The vertex buffer is already bound from initialize()
	glBufferData(GL_ARRAY_BUFFER, m_vertices.size()*sizeof(m_vertices[0]), &m_vertices[0], GL_STATIC_DRAW);		// Send the vertices
	glBindVertexArray(0);
}

void World::draw(glm::mat4& projectionViewMatrix) const {
	glBindVertexArray(m_vao);
	m_shader->activate();
	
	GLuint matrix = glGetUniformLocation(m_shader->getProgramID(), "MVP");
	glm::mat4 mvp = projectionViewMatrix*m_modelMatrix;

	glUniformMatrix4fv(matrix, 1, GL_FALSE, &mvp[0][0]);
	glDrawArrays(GL_TRIANGLES, 0, 3);												// Starting from vertex 0; 3 vertices total -> 1 triangle

	glBindVertexArray(0);
}