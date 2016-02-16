#ifndef ENEMY_H
#define ENEMY_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <cmath>
#include <vector>
#include <string>

#include "character.h"
#include "../block/baseblock.h"
#include "../gametools/datacontainers.h"
#include "../game.h"

//enum explanation
//https://www.youtube.com/watch?v=Pxvvr5FAWxg


class Enemy : public Character {

	enum class MovementState { Read, Move };
	enum class DirectionState { Up, Down, Left, Right, Still };
	
	//target variables -- declared before because of g++ warnings
	std::vector<MovingObjects*> targets;
	BaseBlock* nextBlock;
	BaseBlock* currentBlock;


	//direction-borders -- for sensing target direction
	//M_PI_4 == PI/4
	double rightUp{M_PI_4}; 		//45
	double leftUp{3 * M_PI_4};		//135
	double leftDown{5 * M_PI_4};	//225
	double rightDown{7 * M_PI_4};	//315

	//set angles for sprite rotation
	int lookDown{0};
	int lookLeft{90};
	int lookUp{180};
	int lookRight{270};

	public:
		//characterState
		MovementState moveState;
		//current direction
		DirectionState direction;
		
		//functions
		Enemy(SDL_Texture* texture, int posX, int posY, 
			int width, int height, int speedX, int speedY);
		Enemy(SDL_Texture* texture, int posX, int posY,
			int width, int height);
		Enemy(Game* game, std::string charName, int posX, int posY);
		~Enemy();
		Enemy& operator=(Enemy const& e) = delete;
		Enemy(Enemy const& e) = delete;

		//void Update(float currentTime) override;
		void Update(float currentTime) {};
		void Update(float currentTime, Game* game = nullptr);

		//Getters
		std::vector<MovingObjects*> GetTargets() const;

		//Setters
		void AddTarget(MovingObjects* newTarget);



	private:
		//variables
		float lastTime{0};
		float timeBetweenUpdates{0.2};
		int nextX, nextY;

		//functions
		void CalcDirection(Game* game, double extraAngle = 0);
		double GetAngle(int x1, int x2, int y1, int y2);
		bool ArrivedAtNextBlock();
		MovingObjects* GetNearestTarget(Game* game);

};


#endif