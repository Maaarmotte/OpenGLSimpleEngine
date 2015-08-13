#include "world.h"

World::~World() {
	delete m_shader;
	delete m_texture;
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
	glGenBuffers(1, &m_indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);

	GLint position = glGetAttribLocation(m_shader->getProgramID(), "position");
	glEnableVertexAttribArray(position);
	glVertexAttribPointer(position, 3, GL_FLOAT, GL_FALSE, 5*sizeof(GLfloat), (const GLvoid*)0);

	GLint vertexUV = glGetAttribLocation(m_shader->getProgramID(), "vertexUV");
	glEnableVertexAttribArray(vertexUV);
	glVertexAttribPointer(vertexUV, 2, GL_FLOAT, GL_FALSE, 5*sizeof(GLfloat), (const GLvoid*)(3*sizeof(GLfloat)));
	
	m_texture = new Texture("chat.tga");
	
	glBindVertexArray(0);
}

void World::updateVertices(const unsigned int sizeVertices, const GLfloat *vertices, const unsigned int sizeIndices, const GLuint *indices) {
	m_vertices.reserve(sizeVertices);
	m_vertices.clear();
	m_vertices.insert(m_vertices.begin(), vertices, vertices+sizeVertices);

	m_indices.reserve(sizeIndices);
	m_indices.clear();
	m_indices.insert(m_indices.begin(), indices, indices + sizeIndices);

	glBindVertexArray(m_vao);		// Buffers are already bound in the VAO
	glBufferData(GL_ARRAY_BUFFER, m_vertices.size()*sizeof(m_vertices[0]), &m_vertices[0], GL_STATIC_DRAW);			// Fill the vertex buffer
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size()*sizeof(m_indices[0]), &m_indices[0], GL_STATIC_DRAW);	// Fill the index buffer

	glBindVertexArray(0);
}

void World::draw(glm::mat4& projectionViewMatrix) const {
	glBindVertexArray(m_vao);
	
	m_texture->bind(GL_TEXTURE0);
	m_shader->activate();
	
	GLuint matrix = glGetUniformLocation(m_shader->getProgramID(), "mvp");
	glm::mat4 mvp = projectionViewMatrix*m_modelMatrix;

	glUniformMatrix4fv(matrix, 1, GL_FALSE, &mvp[0][0]);
	glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, 0);		// Use uint indices with 0 offset from m_indices to draw m_indices.size() vertices into triangles

	glBindVertexArray(0);
}