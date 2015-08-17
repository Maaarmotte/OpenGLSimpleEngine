#include "engine.h"

int main() {
	Engine *engine;

	try {
		engine = new Engine(1280, 800);
	}
	catch (const char* msg) {
		std::cerr << "Error: " << msg << std::endl;
		return EXIT_FAILURE;
	}

	engine->loop();

	return EXIT_SUCCESS;
}
