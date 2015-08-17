#include "texture.h"

Texture::Texture() {
	m_textureID = -1;
	m_path = std::string();
}

void Texture::load(std::string path) {
	if (m_textureID < 0) {
		m_path = path;

		m_textureID = SOIL_load_OGL_texture(path.c_str(), SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, 0);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

		glGenerateMipmap(GL_TEXTURE_2D);
	}
}

void Texture::bind(GLuint slot) const {
	glActiveTexture(slot);
	glBindTexture(GL_TEXTURE_2D, m_textureID);
}