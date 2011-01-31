#include "game.h"

int main()
{
	Game* game = new Game();
	
	game->init();
	game->mainLoop();
	game->shutdown();
	
	delete game;
	return 0;
}
