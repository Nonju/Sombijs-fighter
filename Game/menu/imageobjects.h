#ifndef IMAGEOBJECT_H
#define IMAGEOBJECT_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "../polly/objects.h"



class ImageObjects : public Objects {

	public:
		ImageObjects(SDL_Texture*, int posX, int posY,
			int width, int height);
};

#endif