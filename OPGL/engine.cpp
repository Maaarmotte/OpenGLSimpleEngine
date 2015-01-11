#include "engine.h"

using namespace glm;

Engine::Engine() : m_window(NULL), m_vao(NULL), m_world(new World()) {}

int Engine::initialize(int screenWidth, int screenHeight) {
	if (!glfwInit()) {
		std::cerr << "Failed to initialize GLFW" << std::endl;
		return EXIT_FAILURE;
	}

	glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // We want OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //We don't want the old OpenGL 

	// Open a window and create its OpenGL context 
	m_window = glfwCreateWindow(screenWidth, screenHeight, "GLFW Window", NULL, NULL);
	if (m_window == NULL) {
		std::cerr << "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" << std::endl;
		glfwTerminate();
	}

	glfwMakeContextCurrent(m_window); // Initialize GLEW 
	glewExperimental = true; // Needed in core profile 
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		return EXIT_FAILURE;
	}

	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(m_window, GLFW_STICKY_KEYS, GL_TRUE);

	// == Tutorial 2 ==
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	// Initialize the Vertex Array Object (VAO)
	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);

	// Load the "world"
	m_world->initialize();
	m_world->updateVertices();

	return 0;
}

void Engine::loop() const {
	do {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		m_world->draw();
		glfwSwapBuffers(m_window);
		glfwPollEvents();
	} while (glfwGetKey(m_window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(m_window) == 0);
}