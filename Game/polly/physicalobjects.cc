
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "physicalobjects.h"


PhysicalObjects::PhysicalObjects(SDL_Texture* texture, int posX, int posY,
 int width, int height, bool intersectable)
 : Objects(texture, posX, posY, width, height),
  canIntersect{intersectable}, hitPoints{10} {}


bool PhysicalObjects::CollisionDetection(SDL_Rect const& otherRect) {
	int otherX{otherRect.x};
	int otherY{otherRect.y};

	return rectangle.x <= (otherX + otherRect.w) &&
		(rectangle.x + rectangle.w) >= otherX &&
		rectangle.y <= (otherY + otherRect.h) &&
		(rectangle.y + rectangle.h) >= otherY;
}

bool PhysicalObjects::CollisionDetection(PhysicalObjects* otherObject) {
	if (!canIntersect || !otherObject->CanIntersect()) {
		return false;
	}
	int otherX{otherObject->GetX()};
	int otherY{otherObject->GetY()};

	return rectangle.x <= (otherX + otherObject->GetWidth()) &&
		(rectangle.x + rectangle.w) >= otherX &&
		rectangle.y <= (otherY + otherObject->GetHeight()) &&
		(rectangle.y + rectangle.h) >= otherY;
}

bool PhysicalObjects::CheckIfAlive() { return hitPoints < 0; }

//Getters
bool PhysicalObjects::IsAlive() const { return isAlive; }
bool PhysicalObjects::CanIntersect() const { return canIntersect; }
int PhysicalObjects::GetHitPoints() const { return hitPoints; }

//Setters
void PhysicalObjects::SetIsAlive(bool newValue) {
	isAlive = newValue;
}
void PhysicalObjects::SetIntersectable(bool newValue) {
	canIntersect = newValue;
}
void PhysicalObjects::SetHitPoints(int newValue) {
	hitPoints = newValue;
}