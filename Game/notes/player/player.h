#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "../polly/movingobjects.h"
#include "../game.h"

class Player : public MovingObjects {

	public:
		Player(SDL_Texture* texture, int posX, int posY, 
			int width, int height, int speedX, int speedY);
		Player(SDL_Texture* texture, int posX, int posY,
			int width, int height);
		Player(Game* game, std::string charName, int posX, int posY);
		
		void Update(float currentTime);
		void Update(int windowWidth, int windowHeight);

};

#endif