

#include "character.h"
#include "../game.h"

using namespace std;

#if 0
Character::Character(SDL_Texture* texture, int posX, int posY,
 int width, int height, int speedX, int speedY)
: MovingObjects(texture, posX, posY, width, height, speedX, speedY),
		moveState{MovementState::Read},
		direction{DirectionState::Still} {}

Character::Character(SDL_Texture* texture, int posX, int posY,
 int width, int height)
: MovingObjects(texture, posX, posY, width, height),
		moveState{MovementState::Read},
		direction{DirectionState::Still} {}

Character::Character(Game* game, string charName, int posX, int posY)
: MovingObjects(nullptr, posX, posY, 0, 0, 0, 0),
		moveState{MovementState::Read},
		direction{DirectionState::Still} {

	CharData data = game->GetCharData(charName);
	texture = data.texture;
	rectangle.w = data.width;
	rectangle.h = data.height;
	speedX = data.speedX;
	speedY = data.speedY;
}
#endif

Character::Character(SDL_Texture* texture, int posX, int posY,
 int width, int height, int speedX, int speedY)
: MovingObjects(texture, posX, posY, width, height, speedX, speedY)/*,
		moveState{MovementState::Read},
		direction{DirectionState::Still}*/ {}

Character::Character(SDL_Texture* texture, int posX, int posY,
 int width, int height)
: MovingObjects(texture, posX, posY, width, height)/*,
		moveState{MovementState::Read},
		direction{DirectionState::Still}*/ {}

Character::Character(Game* game, string charName, int posX, int posY)
: MovingObjects(nullptr, posX, posY, 0, 0, 0, 0)/*,
		moveState{MovementState::Read},
		direction{DirectionState::Still}*/ {

	CharData data = game->GetCharData(charName);
	texture = data.texture;
	rectangle.w = data.width;
	rectangle.h = data.height;
	speedX = data.speedX;
	speedY = data.speedY;
}

/*void Character::TakeDamage(int amount) {
	hitPoints -= amount;
}*/


#if 0
bool Character::ArrivedAtNextBlock() {
	//cout << "I ArrivedAtNextBlock" << endl;
	switch(direction) { //reWrite after level-implementation
		case DirectionState::Up:
			rectangle.y -= speedY;
			if (GetCenterY() <= nextBlock->GetCenterY()) { return true; }
			else { return false; }
			
		case DirectionState::Down:
			rectangle.y += speedY;
			if (GetCenterY() >= nextBlock->GetCenterY()) { return true; }
			else { return false; }
			
		case DirectionState::Left:
			rectangle.x -= speedX;
			if (GetCenterX() <= nextBlock->GetCenterX()) { return true; }
			else { return false; }

		case DirectionState::Right:
			rectangle.x += speedX;
			if (GetCenterX() >= nextBlock->GetCenterX()) { return true; }
			else { return false; }

		case DirectionState::Still:
		default:
			//moveState = MovementState::Read;
			return false; //error --> go back to read angle
	}
	return false;
}
#endif

