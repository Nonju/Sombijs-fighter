
#include <SDL2/SDL_image.h>

#include "createtexture.h"

using namespace std;

CreateTexture::CreateTexture() {}

SDL_Texture* CreateTexture::GetTexture(SDL_Renderer* renderer,
 string imagePath) {
 	
 	const char* charPath = imagePath.c_str();
	SDL_Surface* tmpSurface{IMG_Load(charPath)};
	SDL_Texture* tmpTexture = SDL_CreateTextureFromSurface(renderer, tmpSurface);

	SDL_FreeSurface(tmpSurface); //free up allocated surface memory

	return tmpTexture;
}