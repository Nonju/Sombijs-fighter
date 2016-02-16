#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <map>
#include <string>

#include "character.h"
#include "../block/baseblock.h"
#include "../game.h"

class Player : public Character {

	enum class MovementState { Read, Move };
	enum class DirectionState { Up, Down, Left, Right, Still };

	public:
		//characterState
		MovementState moveState;
		//current direction
		DirectionState direction;

		Player(SDL_Texture* texture, int posX, int posY, 
			int width, int height, int speedX, int speedY);
		Player(SDL_Texture* texture, int posX, int posY,
			int width, int height);
		Player(Game* game, std::string charName, int posX, int posY);
		
		void Update(float currentTime) {};
		void Update(float currentTime, Game* game = nullptr);

		//Setters

		void SetControlUp(std::string keyName);
		void SetControlDown(std::string keyName);
		void SetControlRight(std::string keyName);
		void SetControlLeft(std::string keyName);
		void SetControlShoot(std::string keyName);
		void SetControlSpecial(std::string keyName);

	private:
		//variables
		BaseBlock* currentBlock;
		BaseBlock* nextBlock;
		int nextX, nextY;
		bool bulletKeyPressed{false};
		bool setUpComplete{false};


		//customcontrols
		std::map<std::string, SDL_Keycode> controls;
		
		//bullet
		SDL_Texture* bulletTexture;
		int bulletWidth, bulletHeight;
		int bulletBaseSpeedX, bulletBaseSpeedY;
		int bulletSpeedX, bulletSpeedY; //are different depending on playerdirection
		int bulletDamage;

		//set angles for sprite rotation
		int lookDown{0};
		int lookLeft{90};
		int lookUp{180};
		int lookRight{270};

		//functions
		void SetDefaultControls();
		void LoadBulletValues(Game* game);
		void ReadInput(Game* game, const Uint8* state);
		bool ArrivedAtNextBlock();

};

#endif
