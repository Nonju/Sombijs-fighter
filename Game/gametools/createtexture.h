#ifndef CREATETEXTURE_H
#define CREATETEXTURE_H

#include <SDL2/SDL_image.h>
#include <string>

class CreateTexture {
	public:
		CreateTexture();
		SDL_Texture* GetTexture(SDL_Renderer* renderer,
		 std::string imagePath);
};

#endif