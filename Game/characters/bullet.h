#ifndef BULLET_H
#define BULLET_H

#include <SDL2/SDL_image.h>

#include "../polly/movingobjects.h"

class Bullet : public MovingObjects {
	public:
		Bullet(SDL_Texture* texture, int posX, int posY,
		int width, int height, int speedX, int speedY, int dmg);

		void Update(float currentTime);

		//Getters
		int GetDamage() const;

		//Setters
		void SetDamage(int newValue);

	private:
		int damage;
};


#endif