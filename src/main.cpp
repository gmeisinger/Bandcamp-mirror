#include "include/game.h"

int main(int argc, char* argv[]) {
	Game game = Game();
	if (!game.init()) {
		std::cout <<  "Failed to initialize!" << std::endl;
		game.close();
		return 1;
	}

	game.run();

	return 0;
}