
#include "bullet.h"

Bullet::Bullet(SDL_Texture* texture, int posX, int posY,
	 int width, int height, int speedX, int speedY, int dmg)
	 :MovingObjects(texture, posX, posY, width, height, speedX, speedY),
	  damage{dmg} {}

void Bullet::Update(float currentTime) {
	rectangle.x += speedX;
	rectangle.y += speedY;
}

//Getters
int Bullet::GetDamage() const { return damage; }

//Setters
void Bullet::SetDamage(int newValue) { damage = newValue; }