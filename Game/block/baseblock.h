#ifndef BLOCK_H
#define BLOCK_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>

#include "../polly/physicalobjects.h"

class Game;

class BaseBlock : public PhysicalObjects {

	protected:
		//variables
		char blockType;
		int coordinateX;
		int coordinateY;

		//functions
		BaseBlock(SDL_Texture* texture, char bT, int posX, int posY,
		 int width, int height, bool passable);
		BaseBlock(SDL_Texture* texture, char bT, int posX, int posY,
		 int width, int height);
		BaseBlock(Game* game, char bT, int posX, int posY);

	public:
		//Getters
		char GetBlockType() const;
		int GetCoordX() const;
		int GetCoordY() const;

		//Setters
		void SetCoordX(int newValue);
		void SetCoordY(int newValue);

		
		

};

#endif