
#include "objects.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

using namespace std;

Objects::Objects(SDL_Texture* t, int pX, int pY, int w, int h)
		: texture{t}, rectangle{pX, pY, w, h} { }

Objects::~Objects() {
	//moved to game-clean-function
	/*SDL_DestroyTexture(texture);
	texture = nullptr;*/
}


void Objects::Draw(SDL_Renderer* renderer) const {
	SDL_RenderCopy(renderer, texture, nullptr, &rectangle);
}

//Getters
SDL_Texture* Objects::GetTexture() const { return texture; }
SDL_Rect Objects::GetRect() const { return rectangle; }
int Objects::GetX() const { return rectangle.x; }
int Objects::GetY() const { return rectangle.y; }
int Objects::GetWidth() const { return rectangle.w; }
int Objects::GetHeight() const { return rectangle.h; }
int Objects::GetCenterX() const { return rectangle.x + (rectangle.w / 2); }
int Objects::GetCenterY() const { return rectangle.y + (rectangle.h / 2); }

//Setters -- add errorhandling?
void Objects::SetX(int newValue) { rectangle.x = newValue; }
void Objects::SetY(int newValue) { rectangle.y = newValue; }
void Objects::SetWidth(int newValue) { rectangle.w = newValue; }
void Objects::SetHeight(int newValue) { rectangle.h = newValue; }
void Objects::SetCenterX(int newValue) {
	rectangle.x = newValue - (rectangle.w / 2);
}
void Objects::SetCenterY(int newValue) {
	rectangle.y = newValue - (rectangle.h / 2);
}

