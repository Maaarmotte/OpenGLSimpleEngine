#include "engine.h"

int main() {
	Engine engine;

	if (engine.initialize(1280, 800) < 0) {
		return EXIT_FAILURE;
	}

	engine.loop();

	return 0;
}
