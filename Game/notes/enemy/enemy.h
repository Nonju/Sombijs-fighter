#ifndef ENEMY_H
#define ENEMY_H

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <cmath>

#include "../polly/movingobjects.h"
#include "../block/baseblock.h"
#include "../gametools/datacontainers.h"
#include "../game.h"

//enum explanation
//https://www.youtube.com/watch?v=Pxvvr5FAWxg


class Enemy : public MovingObjects {

	//enum movementState { Read, Up, Down, Left, Right };
	enum class MovementState { Read, Move };
	enum class DirectionState { Up, Down, Left, Right, Still };
	
	//target variables -- declared before because of g++ warnings
	MovingObjects* target;
	BaseBlock* nextBlock;


	//direction-borders -- for sensing target direction
	//M_PI_4 == PI/4
	double rightUp{M_PI_4};
	double leftUp{3 * M_PI_4};
	double leftDown{5 * M_PI_4};
	double rightDown{7 * M_PI_4};

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
		void Update(float currentTime, Game* game);

		//Getters
		MovingObjects* GetTarget() const;

		//Setters
		void SetTarget(MovingObjects* newTarget);


	private:
		void CalcDirection(Game* game, double angleStart = 0);
		double GetAngle(int x1, int x2, int y1, int y2);
		//bool CheckNextStepIfClear(Game* game);
		void CheckNextStepIfClear(Game* game);
		void Move();

};


#endif