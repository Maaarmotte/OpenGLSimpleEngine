#include "shader.h"

Shader::Shader() : m_vertexShaderID(0), m_fragmentShaderID(0) {}

void Shader::addShaderFile(int type, std::string filename) {
	std::cout << "Loading shader: " << filename << std::endl;
	std::string code;
	std::ifstream stream(filename, std::ios::in);
	if (stream.is_open()) {
		std::string line;
		while (getline(stream, line)) {
			code += "\n" + line;
		}
	}
	addShaderString(type, code);
}

void Shader::addShaderString(int type, std::string source) {
	GLint shader = glCreateShader(type);
	char const *sourcePtr = source.c_str();
	char log[512] = { 0 };
	GLint compiled = GL_FALSE;

	glShaderSource(shader, 1, &sourcePtr, NULL);
	glCompileShader(shader);

	glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
	
	if (compiled != GL_TRUE) {
		glGetShaderInfoLog(shader, sizeof(log)/sizeof(*log), NULL, log);
		std::cout << "Shader compilation error:\n" << log << std::endl;
	}

	switch (type) {
		case GL_VERTEX_SHADER:
			m_vertexShaderID = shader;
			break;
		case GL_FRAGMENT_SHADER:
			m_fragmentShaderID = shader;
			break;
		default:
			std::cerr << "Warning! Unsupported shader, ignoring." << std::endl;
	}
}

void Shader::link() {
	char log[512] = { 0 };
	GLint linked = GL_FALSE;

	m_programID = glCreateProgram();
	glAttachShader(m_programID, m_vertexShaderID);		// Mandatory
	glAttachShader(m_programID, m_fragmentShaderID);	// Mandatory
	glLinkProgram(m_programID);

	glGetProgramiv(m_programID, GL_LINK_STATUS, &linked);

	if (linked != GL_TRUE) {
		glGetProgramInfoLog(m_programID, sizeof(log)/sizeof(*log), NULL, log);
		std::cerr << "Shader linking error:\n" << log << std::endl;
	}

	glDeleteShader(m_vertexShaderID);
	glDeleteShader(m_fragmentShaderID);
}

void Shader::activate() const {
	glUseProgram(m_programID);
}

GLint Shader::getProgramID() const {
	return m_programID;
}