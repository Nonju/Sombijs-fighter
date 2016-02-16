
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "movingobjects.h"

MovingObjects::MovingObjects(SDL_Texture* texture, int posX, int posY,
		 int width, int height, int spX, int spY)
		: PhysicalObjects(texture, posX, posY, width, height, true), 
		speedX{spX}, speedY{spY}, rotationAngle{0} { }

MovingObjects::MovingObjects(SDL_Texture* texture, int posX, int posY,
		 int width, int height)
		: MovingObjects(texture, posX, posY, width, height, 1, 1) { }


void MovingObjects::Draw(SDL_Renderer* renderer) const {
	/*
	int SDL_RenderCopyEx(SDL_Renderer*          renderer,
	                     SDL_Texture*           texture,
	                     const SDL_Rect*        srcrect,
	                     const SDL_Rect*        dstrect,
	                     const double           angle,
	                     const SDL_Point*       center,
	                     const SDL_RendererFlip flip)
	*/
	SDL_RenderCopyEx(renderer, texture, NULL, &rectangle,
		rotationAngle, NULL, SDL_FLIP_NONE);
}

//Getters
int MovingObjects::GetSpeedX() const { return speedX; }
int MovingObjects::GetSpeedY() const { return speedY; }
double MovingObjects::GetRotationAngle() const { return rotationAngle; }

//Setters -- add errorhandling ???
void MovingObjects::SetSpeedX(int newValue) { speedX = newValue; }
void MovingObjects::SetSpeedY(int newValue) { speedY = newValue; }
void MovingObjects::SetRotationAngle(double newValue) { 
	rotationAngle = newValue; 
}