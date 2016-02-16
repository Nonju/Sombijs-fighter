#ifndef CHAR_H
#define CHAR_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>

#include "../polly/movingobjects.h"


class Game;
//enum class MovementState;
//enum class DirectionState;

class Character : public MovingObjects {


	//public:
		//enum class MovementState { Read, Move };
		//enum class DirectionState { Up, Down, Left, Right, Still };

		//characterState
		//MovementState moveState;
		//current direction
		//DirectionState direction;
		
	protected:

		Character(SDL_Texture* texture, int posX, int posY, 
			int width, int height, int speedX, int speedY);
		Character(SDL_Texture* texture, int posX, int posY,
			int width, int height);
		Character(Game* game, std::string charName, int posX, int posY);

		//bool ArrivedAtNextBlock();
	public:

		virtual void Update(float currentTime, Game* game = nullptr) {};

		//void TakeDamage(int amount);
};


#endif