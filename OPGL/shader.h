#ifndef OPGL_SHADER_H
#define OPGL_SHADER_H 1

// C/C++ Standard Libraries
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>

// OpenGL
#include "opengl.h"

class Shader {
	GLint m_programID;
	GLint m_vertexShaderID;
	GLint m_fragmentShaderID;

public:
	Shader();
	void addShaderFile(int type, std::string filename);
	void addShaderString(int type, std::string source);
	void link();
	void activate() const;
	GLint getProgramID() const;
};

#endif