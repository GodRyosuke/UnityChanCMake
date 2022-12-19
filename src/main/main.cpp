#include <iostream>
#include "Game.hpp"

int main(int argc, char** argv)
{
	Game game;
	if (!game.Initialize()) {
		printf("error: Failed to Initialize Game\n");
		return -1;
	}

	game.RunLoop();
	game.Shutdown();
	return 0;
}