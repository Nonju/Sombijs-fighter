#ifndef LEVELHANDLER_H
#define LEVELHANDLER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <vector>
#include <string>

#include "../polly/movingobjects.h"
#include "../gametools/levelloader.h"

class Game;
class BaseBlock;

class LevelHandler {

	public:
		LevelHandler(Game* gamePointer);
		~LevelHandler();

		void Load(SDL_Renderer* renderer);
		bool Update(float currentTime);
		void Draw(SDL_Renderer* renderer);

		std::vector<BaseBlock*> LoadLevel(std::string levelName,
		 int windowWidth, int windowHeight);

		int EnemyCount() const;
		int PlayerCount() const;
		void SetNrOfPlayers(int nr);
		void Reset(); //resets initial values
		
	private:
		//variables
		Game* game;
		int score, playerBaseHP, playerCurrentHP, enemyBaseHP;

		//text
		TTF_Font* textFont;
		SDL_Rect hpRect, scoreRect;
		SDL_Color fontColor;

		//time/spawn variables
		float passedTime;
		bool spawnPlayer;
		int nrOfPlayers;
		bool spawnEnemy;
		int baseNrOfEnemies, maxNrOfEnemies;
		float difficultyRiseTimer, timeSinceDiffRise;
		float enemySpawnTime, timeSinceEnemySpawn;
		float powerupSpawnTime, timeSincePowerupSpawn;

		//functions
		bool CheckIfGameOver();
		void CheckForCollisions();
		void InsertHighScore(std::string filename);
		void TextPrinter(SDL_Renderer* renderer, SDL_Rect rect,
		 std::string text);

};

#endif
