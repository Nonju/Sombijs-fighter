#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "../gametools/datacontainers.h"
#include "baseblock.h"
#include "../game.h"

BaseBlock::BaseBlock(SDL_Texture* texture, char bT, int posX, int posY,
		 int width, int height, bool canIntersect)
		: PhysicalObjects(texture, posX, posY, width, height, canIntersect),
		 blockType{bT} {}	 

BaseBlock::BaseBlock(SDL_Texture* texture, char blockType, int posX, int posY,
		 int width, int height)
		: BaseBlock(texture, blockType, posX, posY, width, height, false) {}

BaseBlock::BaseBlock(Game* game, char blockType, int posX, int posY)
		: BaseBlock(nullptr, blockType, posX, posY, 1, 1) {

	BlockData data = game->GetBlockData(blockType);
	texture = data.texture;
	rectangle.w = data.width;
	rectangle.h = data.height;
	hitPoints = data.hitPoints;
	canIntersect = data.intersectable;
}


//Getters
char BaseBlock::GetBlockType() const { return blockType; }


int BaseBlock::GetCoordX() const { return coordinateX; }
int BaseBlock::GetCoordY() const { return coordinateY; }

//Setters
void BaseBlock::SetCoordX(int newValue) {
	if (newValue < 0) { newValue = 0; }
	coordinateX = newValue;
}
void BaseBlock::SetCoordY(int newValue) {
	if (newValue < 0) { newValue = 0; }
	coordinateY = newValue;
}

