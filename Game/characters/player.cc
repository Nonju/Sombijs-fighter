
#include "player.h"
#include "../gametools/datacontainers.h" //for type CharData
#include "bullet.h"

using namespace std;

Player::Player(SDL_Texture* texture, int posX, int posY,
 int width, int height, int speedX, int speedY)
: Character(texture, posX, posY, width, height, speedX, speedY),
		moveState{MovementState::Read}, 
		direction{DirectionState::Still},
		currentBlock{nullptr}, nextBlock{nullptr} {
			SetDefaultControls();
		}

Player::Player(SDL_Texture* texture, int posX, int posY, int width, int height)
: Character(texture, posX, posY, width, height),
		moveState{MovementState::Read}, 
		direction{DirectionState::Still},
		currentBlock{nullptr}, nextBlock{nullptr} {
			SetDefaultControls();
		}

Player::Player(Game* game, string charName, int posX, int posY)
: Character(game, charName, posX, posY),
		moveState{MovementState::Read}, 
		direction{DirectionState::Still},
		currentBlock{nullptr}, nextBlock{nullptr} {
			SetDefaultControls();
		}


void Player::SetDefaultControls() {
	controls.insert(make_pair("UP", SDL_SCANCODE_W));
	controls.insert(make_pair("DOWN", SDL_SCANCODE_S));
	controls.insert(make_pair("RIGHT", SDL_SCANCODE_D));
	controls.insert(make_pair("LEFT", SDL_SCANCODE_A));
	controls.insert(make_pair("SHOOT", SDL_SCANCODE_SPACE));
	controls.insert(make_pair("SPECIAL", SDL_SCANCODE_E));
}

void Player::LoadBulletValues(Game* game) {

	//bullet values
	CharData data = game->GetCharData("Bullet1");
	bulletTexture = data.texture;
	bulletWidth = data.width;
	bulletHeight = data.height;
	bulletBaseSpeedX = data.speedX;
	bulletBaseSpeedY = data.speedY;
	bulletDamage = 1;

	bulletSpeedX = 0;
	bulletSpeedY = bulletBaseSpeedY;

}

void Player::Update(float currentTime, Game* game) {
	if (!setUpComplete) { //quickfix
		setUpComplete = true;
		LoadBulletValues(game);
	}

	//check if alive
	if (hitPoints <= 0) { isAlive = false; }

	//read keyboardstate
	const Uint8 *state = SDL_GetKeyboardState(NULL);

	//ReadInput(game, state);
	switch (moveState) {
		case MovementState::Move:
			if (ArrivedAtNextBlock()) {
				moveState = MovementState::Read;
			}
			break;
		case MovementState::Read:
		default:
			ReadInput(game, state);
			break;
	}
	
	if (state[controls.at("SHOOT")] && !bulletKeyPressed) {
		//shoot bullet
		bulletKeyPressed = true;
		game->InsertGameObject(new Bullet{bulletTexture, GetCenterX(),
			GetCenterY(), bulletWidth, bulletHeight,
			 bulletSpeedX, bulletSpeedY, bulletDamage});
	}
	else if (!state[controls.at("SHOOT")]) { bulletKeyPressed = false; }

}

void Player::ReadInput(Game* game, const Uint8* state) {
	//Get current position
	currentBlock = game->GetCharLocation(this);
	nextX = currentBlock->GetCoordX();
	nextY = currentBlock->GetCoordY();

	//handle player-movement
	//also handles current-facing-direction + current bulletSpeeds
	
	//X
	if (state[controls.at("LEFT")]) { //left
		direction = DirectionState::Left;
		nextX--;

		rotationAngle = lookLeft;
		bulletSpeedX = -bulletBaseSpeedX;
		bulletSpeedY = 0;
		
	}
	else if (state[controls.at("RIGHT")]) { //right
		direction = DirectionState::Right;
		nextX++;

		rotationAngle = lookRight;
		bulletSpeedX = bulletBaseSpeedX;
		bulletSpeedY = 0;
		
	}
	//Y
	else if (state[controls.at("UP")]) { //up
		direction = DirectionState::Up;
		nextY--;

		rotationAngle = lookUp;
		bulletSpeedX = 0;
		bulletSpeedY = -bulletBaseSpeedY;

	}
	else if (state[controls.at("DOWN")]) { //down
		direction = DirectionState::Down;
		nextY++;

		rotationAngle = lookDown;
		bulletSpeedX = 0;
		bulletSpeedY = bulletBaseSpeedY;
	}
	if (nextX == currentBlock->GetCoordX() &&
		nextY == currentBlock->GetCoordY()) {
		direction = DirectionState::Still;
	}
	else if (!game->CheckCoordIfAvailable(nextX, nextY)) {
		nextBlock = game->GetBlockAtCoord(nextX, nextY);
		moveState = MovementState::Move;
	}

}

bool Player::ArrivedAtNextBlock() {
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
			return false; //error --> go back to read input
	}
	return false;
}

//Setters

void Player::SetControlUp(string keyName) {
	controls.at("UP") = SDL_GetScancodeFromName(keyName.c_str());
}
void Player::SetControlDown(string keyName) {
	controls.at("DOWN") = SDL_GetScancodeFromName(keyName.c_str());
}
void Player::SetControlRight(string keyName) {
	controls.at("RIGHT") = SDL_GetScancodeFromName(keyName.c_str());
}
void Player::SetControlLeft(string keyName) {
	controls.at("LEFT") = SDL_GetScancodeFromName(keyName.c_str());
}
void Player::SetControlShoot(string keyName) {
	controls.at("SHOOT") = SDL_GetScancodeFromName(keyName.c_str());
}
void Player::SetControlSpecial(string keyName) {
	controls.at("SPECIAL") = SDL_GetScancodeFromName(keyName.c_str());
}

