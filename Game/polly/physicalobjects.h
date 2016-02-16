#ifndef PHYSICALOBJECTS_H
#define PHYSICALOBJECTS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "objects.h"

class PhysicalObjects : public Objects {


	protected: 
		//variables
		bool isAlive{true};
		bool canIntersect;
		int hitPoints;
		
		//functions
		PhysicalObjects(SDL_Texture* texture, int posX, int posY,
		 int width, int height, bool intersectable);

	public: 

		bool CollisionDetection(SDL_Rect const& otherRect);
		bool CollisionDetection(PhysicalObjects* otherObject);
		bool CheckIfAlive();

		//Getters
		bool IsAlive() const;
		bool CanIntersect() const;
		int GetHitPoints() const;

		//Setters
		void SetIsAlive(bool newValue);
		void SetIntersectable(bool newValue);
		void SetHitPoints(int newValue);

};

#endif