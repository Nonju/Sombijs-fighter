#ifndef CHARDATA_H
#define CHARDATA_H

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

struct CharData {
	std::string charName;
	SDL_Texture* texture;
	int width;
	int height;
	int speedX;
	int speedY;
};

struct BlockData {
	std::string blockName;
	char blockType;
	SDL_Texture* texture;
	int width;
	int height;
	int hitPoints;
	bool intersectable;
	std::string charName;
};

struct ControlData {
	std::string charName;
	std::string up;
	std::string down;
	std::string left;
	std::string right;
	std::string shoot;
	std::string special;
};

#endif