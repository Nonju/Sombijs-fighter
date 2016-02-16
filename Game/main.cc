
#include "game.h"

int main() {

	Game game;
	//game.Init("Sombijs-fighter", 800, 600);
	game.Init("Sombijs-fighter", 1024, 768);

	while ( game.StillRunning() ) {
		game.EventHandler();
		game.Update();
		game.Draw();
	}

	//after game's done --> clean assets
	//game.Clean(); //taken care of in game-destructor


	return 0;
}