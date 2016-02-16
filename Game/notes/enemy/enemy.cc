#include <iostream> //remove

#include "enemy.h"
#include "../block/baseblock.h"

using namespace std;


Enemy::Enemy(SDL_Texture* texture, int posX, int posY, 
		int width, int height, int speedX, int speedY)
		:MovingObjects(texture, posX, posY, width, height,
		speedX, speedY), target{nullptr}, nextBlock{nullptr},
		 moveState{MovementState::Read},
		direction{DirectionState::Still} { }

Enemy::Enemy(SDL_Texture* texture, int posX, int posY, 
		int width, int height)
		:Enemy(texture, posX, posY, width, height, 1, 1) { }

Enemy::Enemy(Game* game, std::string charName, int posX, int posY)
:MovingObjects(nullptr, posX, posY, 1, 1, 1, 1) {

	CharData data = game->GetCharData(charName);
	texture = data.texture;
	rectangle.w = data.width;
	rectangle.h = data.height;
	speedX = data.speedX;
	speedY = data.speedY;
}

Enemy::~Enemy() {
	//delete target;
	target = nullptr;
}

void Enemy::Update(float currentTime, Game* game) {
	//check if alive
	if (hitPoints < 0) {
		isAlive = false;
	}

	switch (moveState) {
		case MovementState::Move:
			/*if (CheckNextStepIfClear(game)) {
				Move();	
			}*/
			//CheckNextStepIfClear(game);
			Move();
			moveState = MovementState::Read; //change (???)
			break;

		//calculate the next 3 steps towards target (???)
		case MovementState::Read:
		default: //MovementState::Read
			CalcDirection(game);
			moveState = MovementState::Move; //should this be here???
			break;

	}
	
}

void Enemy::CalcDirection(Game* game, double angleStart) {
	//k == (y2 - y1) / (x2 - x1)
	//angle == atan2(deltaY, deltaX) * 180 / PI
	if (target != nullptr) {

		#if 0
		//for calcing based on pixel position
		double tmpX{static_cast<double>((GetTarget()->GetX() - GetX()))};
		double tmpY{static_cast<double>((GetTarget()->GetY() - GetY()))};
		double angle{atan2(tmpY, tmpX)}; /* * 180 / M_PI*/
		#endif
		#if 1
		//for calcing based on coordinate position
		BaseBlock* currentPos = game->GetCharLocation(this);
		BaseBlock* targetPos = game->GetCharLocation(target);
		double angle{GetAngle(currentPos->GetCoordX(), targetPos->GetCoordX(),
				currentPos->GetCoordY(), targetPos->GetCoordY()) + angleStart};
		currentPos = nullptr;
		targetPos = nullptr;
		#endif

		if (angle < 0) { angle += (2 * M_PI); } //keeps angle positive
		//cout << "Angle: " << angle << endl;

		if (angle > rightUp && angle <= leftUp) { //down
			direction = DirectionState::Down;
		}
		else if (angle > leftDown && angle <= rightDown) { //up
			direction = DirectionState::Up;
		}
		else if (angle > leftUp && angle <= leftDown) { //left
			direction = DirectionState::Left;
		}
		else if ((angle <= rightUp && angle >= 0) ||
		 (angle >= rightDown && angle <= (2 * M_PI))) { //right
			direction = DirectionState::Right;
		}
		else { //if error
			direction = DirectionState::Still;
		}
	}
	else {
		//target = this;
		direction = DirectionState::Still;
	}
}

//bool Enemy::CheckNextStepIfClear(Game* game) {
void Enemy::CheckNextStepIfClear(Game* game) {
	if (nextBlock != nullptr) {
		int nextX{nextBlock->GetCoordX()};
		int nextY{nextBlock->GetCoordY()};

		if (game->CheckCoordIfAvailable(nextX, nextY)) {
			//return true;
			//move();
		}
		else { //if coordinate is unavailable --> rotate 90 degrees and try again
			CalcDirection(game, M_PI_2);
		}	
	}
	else {
		nextBlock = game->GetCharLocation(this);
		//nextBlock->SetCoordX(nextBlock->GetCoordX() -1);
	}
	//return false;
	
}

void Enemy::Move() {
	switch(direction) { //reWrite after level-implementation
		case DirectionState::Up:
			//cout << "Vinkel: Up" << endl;
			rectangle.y -= speedY;
			break;
		case DirectionState::Down:
			//cout << "Vinkel: Down" << endl;
			rectangle.y += speedY;
			break;
		case DirectionState::Left:
			//cout << "Vinkel: Left" << endl;
			rectangle.x -= speedX;
			break;
		case DirectionState::Right:
			//cout << "Vinkel: Right" << endl;
			rectangle.x += speedX;
			break;
		case DirectionState::Still:
		default:
			//cout << "Vinkel: Stilla" << endl;
			moveState = MovementState::Read;
			break;
	}
}

//Getters
MovingObjects* Enemy::GetTarget() const { return target; }

/*double Enemy::GetGradient() {
	return (GetTarget()->GetY() - GetY()) / (GetTarget()->GetX() - GetX());
}*/
double Enemy::GetAngle(int x1, int x2, int y1, int y2) {
	return atan2(static_cast<double>(y2 - y1), static_cast<double>(x2 - x1));
}

//Setters
void Enemy::SetTarget(MovingObjects* newTarget) { 
	target = newTarget; 
}





