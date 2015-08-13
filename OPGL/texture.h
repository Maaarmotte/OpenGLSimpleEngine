#ifndef OPGL_TEXTURE_H
#define OPGL_TEXTURE_H 1

// C/C++ Standard Libraries
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>

// OpenGL
#include "opengl.h"
#include <SOIL2.h>

// Program Includes

class Texture {
	GLuint m_textureID;
	std::string m_path;

public:
	Texture(std::string path);
	~Texture();
	void bind(GLuint slot);
};

#endif