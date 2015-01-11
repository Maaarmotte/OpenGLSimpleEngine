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

// OpenGL Related Libraries
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

class Shader {
	GLint m_programID;
	GLint m_vertexShaderID;
	GLint m_fragmentShaderID;

public:
	void loadFromFile(std::string vertexFile, std::string fragmentFile);
	void loadFromString(std::string vertexString, std::string fragmentString);
	void compile();
	void activate() const;
	GLint getProgramID() const;
};

#endif