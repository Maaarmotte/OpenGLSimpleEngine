#include "shader.h"

void Shader::loadFromFile(std::string vertexFile, std::string fragmentFile) {
	std::cout << "Loading vertex shader: " << vertexFile << std::endl;
	std::string vertexShaderCode;
	std::ifstream vertexShaderStream(vertexFile, std::ios::in);
	if (vertexShaderStream.is_open())
	{
		std::string line = "";
		while (getline(vertexShaderStream, line))
			vertexShaderCode += "\n" + line;
		vertexShaderStream.close();
	}

	std::cout << "Loading fragment shader: " << fragmentFile << std::endl;
	std::string fragmentShaderCode;
	std::ifstream fragmentShaderStream(fragmentFile, std::ios::in);
	if (fragmentShaderStream.is_open()){
		std::string line = "";
		while (getline(fragmentShaderStream, line))
			fragmentShaderCode += "\n" + line;
		fragmentShaderStream.close();
	}

	loadFromString(vertexShaderCode, fragmentShaderCode);
}

void Shader::loadFromString(std::string vertexString, std::string fragmentString) {
	GLint result = GL_FALSE;
	int infoLogLength;

	m_vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	m_fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	
	std::cout << "Compiling vertex shader" << std::endl;
	char const * vertexSourcePointer = vertexString.c_str();
	glShaderSource(m_vertexShaderID, 1, &vertexSourcePointer, NULL);
	glCompileShader(m_vertexShaderID);

	glGetShaderiv(m_vertexShaderID, GL_COMPILE_STATUS, &result);
	glGetShaderiv(m_vertexShaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
	std::vector<char> vertexShaderErrorMessage(infoLogLength);
	glGetShaderInfoLog(m_vertexShaderID, infoLogLength, NULL, &vertexShaderErrorMessage[0]);
	std::cout << vertexShaderErrorMessage[0] << std::endl;

	std::cout << "Compiling fragment shader" << std::endl;
	char const * fragmentSourcePointer = fragmentString.c_str();
	glShaderSource(m_fragmentShaderID, 1, &fragmentSourcePointer, NULL);
	glCompileShader(m_fragmentShaderID);

	glGetShaderiv(m_fragmentShaderID, GL_COMPILE_STATUS, &result);
	glGetShaderiv(m_fragmentShaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
	std::vector<char> fragmentShaderErrorMessage(infoLogLength);
	glGetShaderInfoLog(m_fragmentShaderID, infoLogLength, NULL, &fragmentShaderErrorMessage[0]);
	std::cout << fragmentShaderErrorMessage[0] << std::endl;
}

void Shader::compile(){
	GLint result = GL_FALSE;
	int infoLogLength;

	std::cout << "Linking program" << std::endl;
	m_programID = glCreateProgram();
	glAttachShader(m_programID, m_vertexShaderID);
	glAttachShader(m_programID, m_fragmentShaderID);
	glLinkProgram(m_programID);

	glGetProgramiv(m_programID, GL_LINK_STATUS, &result);
	glGetProgramiv(m_programID, GL_INFO_LOG_LENGTH, &infoLogLength);
	std::vector<char> programErrorMessage(std::max(infoLogLength, int(1)));
	glGetProgramInfoLog(m_programID, infoLogLength, NULL, &programErrorMessage[0]);
	std::cout << programErrorMessage[0] << std::endl;

	glDeleteShader(m_vertexShaderID);
	glDeleteShader(m_fragmentShaderID);
}

void Shader::activate() const {
	glUseProgram(m_programID);
}

GLint Shader::getProgramID() const {
	return m_programID;
}