#ifndef MOVINGOBJECTS_H
#define MOVINGOBJECTS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "physicalobjects.h"

//class Game;

class MovingObjects : public PhysicalObjects {

	protected:
		//variables
		int speedX;
		int speedY;
		double rotationAngle;

		//functions
		//constructor with speed
		MovingObjects(SDL_Texture* texture, int posX, int posY,
		 int width, int height, int speedX, int speedY);

		//constructor with default speed
		MovingObjects(SDL_Texture* texture, int posX, int posY,
		 int width, int height);
		

	public:


		void Draw(SDL_Renderer* renderer) const;

		//Getters
		int GetSpeedX() const;
		int GetSpeedY() const;
		double GetRotationAngle() const;

		//Setters
		void SetSpeedX(int newValue);
		void SetSpeedY(int newValue);
		void SetRotationAngle(double newValue);

};

#endif