#include "engine.h"

int main() {
	Engine engine;

	if (engine.initialize() < 0) {
		return EXIT_FAILURE;
	}

	engine.loop();

	return 0;
}
