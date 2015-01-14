#include "engine.h"

Engine::Engine() : m_window(NULL), m_vao(NULL), m_world(new World()) {}

Engine::~Engine() {
	delete m_world;
}

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

	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	// Open a window and create its OpenGL context 
	m_window = glfwCreateWindow(screenWidth, screenHeight, "GLFW Window", NULL, NULL);
	if (m_window == NULL) {
		std::cerr << "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" << std::endl;
		glfwTerminate();
	}

	glfwMakeContextCurrent(m_window); // Initialize GLEW 
	glewExperimental = true; // Needed in core profile 
	if (glewInit() != GLEW_OK) {
		std::cerr << "Failed to initialize GLEW" << std::endl;
		return EXIT_FAILURE;
	}

	// Ensure we can capture the escape key being pressed below
	//glfwSetInputMode(m_window, GLFW_STICKY_KEYS, GL_TRUE);

	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	// View Matrix
	m_viewMatrix = glm::lookAt(
		glm::vec3(1, 0.75, 0.75),		// Camera is at (4,3,3), in World Space
		glm::vec3(0, 0, 0),		// and looks at the origin
		glm::vec3(0, 1, 0));	// Head is up (set to 0,-1,0 to look upside-down)

	m_projectionMatrix = glm::perspective(
		60.0f,			// Field of View
		4.0f / 3.0f,	// Ratio
		0.1f,			// Near plane
		100.0f);		// Far plane

	m_viewProjectionMatrix = m_projectionMatrix*m_viewMatrix;

	// Initialize the Vertex Array Object (VAO)
	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);

	// Load the "world"
	GLfloat vertices[9] = { -1.0f, -1.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f };
	GLuint indices[3] = { 0, 1, 2 };

	m_world->initialize();
	m_world->updateVertices(sizeof(vertices)/sizeof(*vertices), vertices, sizeof(indices)/sizeof(*indices), indices);

	return 0;
}

void Engine::loop() {
	do {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		m_world->draw(m_viewProjectionMatrix);
		glfwSwapBuffers(m_window);
		glfwPollEvents();
	} while (glfwGetKey(m_window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(m_window) == 0);
}