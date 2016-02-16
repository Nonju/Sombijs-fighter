#ifndef BLOCKS_H
#define BLOCKS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>

#include "baseblock.h"
#include "../polly/movingobjects.h"
//game.h already included in baseclass (baseblock.h)

class EmptyBlock : public BaseBlock {
	public:
		//functions
		EmptyBlock(SDL_Texture* texture, int posX, int posY,
		 int width, int height, bool passable);
		EmptyBlock(SDL_Texture* texture, int posX, int posY,
		 int width, int height);
		EmptyBlock(Game* game, char blockType, int posX, int posY);

		void Update(float currentTime) {};
};

class WallBlock : public BaseBlock {
	public:
		//functions
		WallBlock(SDL_Texture* texture, int posX, int posY,
		 int width, int height, bool passable);
		WallBlock(SDL_Texture* texture, int posX, int posY,
		 int width, int height);
		WallBlock(Game* game, char blockType, int posX, int posY);
		

		void Update(float currentTime) {};
};

class Spawner : public BaseBlock {
	public:
		//functions
		Spawner(SDL_Texture* texture, int posX, int posY,
		 int width, int height, bool passable);
		Spawner(SDL_Texture* texture, int posX, int posY,
		 int width, int height);
		Spawner(Game* game, char blockType, int posX, int posY);

		void Update(float currentTime) {}; //not used
		virtual void Spawn(Game* game, int charHitPoints = 1,
		 int charNr = 1) = 0;
};

class PlayerSpawn : public Spawner {
	public:
		//functions
		PlayerSpawn(SDL_Texture* texture, int posX, int posY,
		 int width, int height, bool passable);
		PlayerSpawn(SDL_Texture* texture, int posX, int posY,
		 int width, int height);
		PlayerSpawn(Game* game, char blockType, int posX, int posY);

		void Spawn(Game* game, int charHitPoints = 1,
		 int charNr = 1) override;
};

class EnemySpawn : public Spawner {
	public:
		//functions
		EnemySpawn(SDL_Texture* texture, int posX, int posY,
		 int width, int height, bool passable);
		EnemySpawn(SDL_Texture* texture, int posX, int posY,
		 int width, int height);
		EnemySpawn(Game* game, char blockType, int posX, int posY);


		void Spawn(Game* game, int charHitPoints = 1,
		 int charNr = 1) override;
};

class PowerupSpawn : public Spawner { 
	public:
		//functions
		PowerupSpawn(SDL_Texture* texture, int posX, int posY,
		 int width, int height, bool passable);
		PowerupSpawn(SDL_Texture* texture, int posX, int posY,
		 int width, int height);
		PowerupSpawn(Game* game, char blockType, int posX, int posY);

		void Spawn(Game* game, int charHitPoints = 1,
		 int charNr = 1) override;
};

#endif






