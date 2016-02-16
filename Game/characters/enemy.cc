
#include "enemy.h"
#include "../block/baseblock.h"

using namespace std;



Enemy::Enemy(SDL_Texture* texture, int posX, int posY,
 int width, int height, int speedX, int speedY)
: Character(texture, posX, posY, width, height, speedX, speedY),
		currentBlock{nullptr},
		moveState{MovementState::Read},
		direction{DirectionState::Still} {}

Enemy::Enemy(SDL_Texture* texture, int posX, int posY, int width, int height)
: Character(texture, posX, posY, width, height),
		currentBlock{nullptr},
		moveState{MovementState::Read},
		direction{DirectionState::Still} {}

Enemy::Enemy(Game* game, string charName, int posX, int posY)
: Character(game, charName, posX, posY),
		currentBlock{nullptr},
		moveState{MovementState::Read},
		direction{DirectionState::Still} {}



Enemy::~Enemy() {
	currentBlock = nullptr;
	nextBlock = nullptr;
}

void Enemy::Update(float currentTime, Game* game) {
	//check if alive
	if (hitPoints <= 0) { isAlive = false; }

	switch (moveState) {
		case MovementState::Move:
			if (ArrivedAtNextBlock()) {
				moveState = MovementState::Read;
			}
			break;

		case MovementState::Read:
		default: //MovementState::Read
			if ((currentTime - lastTime) >= timeBetweenUpdates) {
				lastTime = currentTime;
				CalcDirection(game);
				if (direction != DirectionState::Still) {
					moveState = MovementState::Move;	
				}
				
			}
			break;
	}
	
}

void Enemy::CalcDirection(Game* game, double extraAngle) {
	//k == (y2 - y1) / (x2 - x1)
	//angle == atan2(deltaY, deltaX) * 180 / PI
	double angle{};
	MovingObjects* target = GetNearestTarget(game);
	if (target != nullptr) {

		//for calcing based on coordinate position
		currentBlock = game->GetCharLocation(this); 
		if (currentBlock == game->GetCharLocation(target)) {
			direction = DirectionState::Still;
			rotationAngle = lookDown;
			return;
		}

		nextX = currentBlock->GetCoordX();
		nextY = currentBlock->GetCoordY();
		currentBlock = nullptr;
		if (extraAngle == 0) {
			BaseBlock* targetPos = game->GetCharLocation(target);
			angle = (GetAngle(nextX, targetPos->GetCoordX(),
					nextY, targetPos->GetCoordY()) + extraAngle);
			targetPos = nullptr;
		}
		else {
			angle = extraAngle;
		}

		if (angle < 0) { angle += (2 * M_PI); } //keeps angle positive
		else if (angle > (2 * M_PI)) { angle -= (2 * M_PI); }

		//REDO INTO SWITCH/CASE
		if (angle > rightUp && angle <= leftUp) { //down
			direction = DirectionState::Down;

			rotationAngle = lookDown;
			nextY++;
		}
		else if (angle > leftDown && angle <= rightDown) { //up			
			direction = DirectionState::Up;

			rotationAngle = lookUp;
			nextY--;
		}
		else if (angle > leftUp && angle <= leftDown) { //left
			direction = DirectionState::Left;

			rotationAngle = lookLeft;
			nextX--;
		}
		else if ((angle <= rightUp && angle >= 0) ||
		 (angle >= rightDown && angle <= (2 * M_PI))) { //right
			direction = DirectionState::Right;

			rotationAngle = lookRight;
			nextX++;
		}

		#if 1
		if (game->CheckCoordIfAvailable(nextX, nextY)) {
			CalcDirection(game, (angle + M_PI_2));
		}
		else {
			nextBlock = game->GetBlockAtCoord(nextX, nextY);
		}
		#endif
	}
	else {
		direction = DirectionState::Still;
	}
	
}

bool Enemy::ArrivedAtNextBlock() {
	switch(direction) { 
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
			return false; //error --> go back to read angle
	}
	return false;
}

//Getters
vector<MovingObjects*> Enemy::GetTargets() const { return targets; }

double Enemy::GetAngle(int x1, int x2, int y1, int y2) {
	return atan2(static_cast<double>(y2 - y1), static_cast<double>(x2 - x1));
}

MovingObjects* Enemy::GetNearestTarget(Game* game) {
	MovingObjects* newTarget{nullptr};
	double closestDistance{-1};
	currentBlock = game->GetCharLocation(this);
	for (MovingObjects* target : targets) {
		BaseBlock* targetPos = game->GetCharLocation(target);
		double xDist{static_cast<double>(abs(targetPos->GetCoordX()
		 - currentBlock->GetCoordX()))};
		double yDist{static_cast<double>(abs(targetPos->GetCoordY()
		 - currentBlock->GetCoordY()))};

		double hyp{sqrt(pow(10, xDist) + pow(10, yDist))};
		if (closestDistance == -1 || hyp < closestDistance) { 
			closestDistance = hyp;
			newTarget = target;
		}

	}

	return newTarget;
}

//Setters
void Enemy::AddTarget(MovingObjects* newTarget) {
	targets.push_back(newTarget);
}





