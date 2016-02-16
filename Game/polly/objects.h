#ifndef OBJECTS_H
#define OBJECTS_H

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>


class Objects {

	protected:
		//variables
		SDL_Texture* texture;
		SDL_Rect rectangle;

		//functions
		Objects(SDL_Texture* t, int pX, int pY, int w, int h);
		virtual ~Objects();
		Objects& operator=(Objects const& o) = delete;
		Objects(Objects const& o) = delete;

	public:
		virtual void Update(float currentTime) = 0;
		void Draw(SDL_Renderer* renderer) const;

		//getters
		SDL_Texture* GetTexture() const;
		SDL_Rect GetRect() const;
		int GetX() const;
		int GetY() const;
		int GetWidth() const;
		int GetHeight() const;
		int GetCenterX() const;
		int GetCenterY() const;

		//setters
		void SetX(int newValue);
		void SetY(int newValue);
		void SetWidth(int newValue);
		void SetHeight(int newValue);
		void SetCenterX(int newValue);
		void SetCenterY(int newValue);

};

#endif