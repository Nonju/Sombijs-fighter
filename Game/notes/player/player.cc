#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "player.h"
#include "../gametools/datacontainers.h" //for type CharData

using namespace std;

Player::Player(SDL_Texture* texture, int posX, int posY,
 int width, int height, int speedX, int speedY)
: MovingObjects(texture, posX, posY, width, height, speedX, speedY) {}

Player::Player(SDL_Texture* texture, int posX, int posY, int width, int height)
: MovingObjects(texture, posX, posY, width, height) {}

Player::Player(Game* game, string charName, int posX, int posY)
: MovingObjects(nullptr, posX, posY, 0, 0, 0, 0) {

	CharData data = game->GetCharData(charName);
	texture = data.texture;
	rectangle.w = data.width;
	rectangle.h = data.height;
	speedX = data.speedX;
	speedY = data.speedY;
}


//probably the one thats going to be used
void Player::Update(float currentTime) { 
	//read keyboardstate
	const Uint8 *state = SDL_GetKeyboardState(NULL);

	//handle player-movement
	//X
	if (state[SDL_SCANCODE_A]) { //left

	}
	else if (state[SDL_SCANCODE_D]) { //right

	}
	//Y
	if (state[SDL_SCANCODE_W]) { //up

	}
	else if (state[SDL_SCANCODE_S]) { //down
		
	}

}

void Player::Update(int windowWidth, int windowHeight) {

	//read keyboardstate
	const Uint8 *state = SDL_GetKeyboardState(NULL);

	//handle player-movement
	//X
	if (state[SDL_SCANCODE_A] && rectangle.x > 0) {
		rectangle.x -= speedX;
	}
	else if (state[SDL_SCANCODE_D] 
		&& rectangle.x < (windowWidth - rectangle.w)) {
		rectangle.x += speedX;
	}
	//Y
	if (state[SDL_SCANCODE_W] && rectangle.y > 0) {
		rectangle.y -= speedY;
	}
	else if (state[SDL_SCANCODE_S] 
		&& rectangle.y < (windowHeight - rectangle.h)) {
		rectangle.y += speedY;
	}

}