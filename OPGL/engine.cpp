#include "engine.h"

Engine::Engine(int screenWidth, int screenHeight) : m_camera(45.0f, (float)screenWidth / screenHeight, 0.1f, 100.0f) {
	std::cout << "Initializing engine..." << std::endl;
	if (!glfwInit()) {
		throw "Failed to initialize GLFW";
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
		throw "Failed to initialize GLEW";
	}

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	// Ensure we can capture the escape key being pressed below
	//glfwSetInputMode(m_window, GLFW_STICKY_KEYS, GL_TRUE);

	m_camera.setPos(0.0f, 0.45f, 0.0f);
	m_camera.setAngle(0.0f, 0.0f, 0.0f);

	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	// Load the "world"			// Vertices				// UVs
	GLfloat vertices[20] = {	-1.0f,	0.0f,	-1.0f,	0.0f, 1.0f,
								-1.0f,	0.0f,	1.0f,	0.0f, 0.0f,
								1.0f,	0.0f,	-1.0f,	1.0f, 1.0f,
								1.0f,	0.0f,	1.0f,	1.0f, 0.0f };
	
	GLuint indices[6] = { 0, 1, 3, 0, 2, 3 };

	std::cout << "Initializing world..." << std::endl;
	m_world.load();
	m_world.updateVertices(sizeof(vertices) / sizeof(*vertices), vertices, sizeof(indices) / sizeof(*indices), indices);
}

void Engine::loop() {
	double t;
	do {
		t = glfwGetTime();
		std::cout << "\rFPS: " << 1 / (t - m_drawTime);
		m_drawTime = t;

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		m_camera.updateFromController(*m_window);
		m_world.draw(m_camera.getProjectionViewMatrix());

		glfwSwapBuffers(m_window);
		glfwPollEvents();
	} while (glfwGetKey(m_window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(m_window) == 0);
}
