#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>
#include <string>

#include "polly/movingobjects.h"
#include "gametools/levelloader.h"
#include "gametools/attrloader.h" //for loading object data
#include "gametools/datacontainers.h" //for storing object data
#include "levelhandler/levelhandler.h"
#include "menu/menu.h"

class BaseBlock;

class Game {

	public:
		enum class GameState {Menu, SinglePlayer, MultiPlayer, Quit};
		GameState gameState;

		Game();
		~Game();

		//main functions
		void Init(const char* title, int windowWidth, int windowHeight);
		bool StillRunning();
		void EventHandler();
		void Update();
		void Draw();
		void Clean();
		void Quit();

		//data functions
		int GetWindowWidth() const;
		int GetWindowHeight() const;

		CharData GetCharData(std::string charName);
		BlockData GetBlockData(std::string blockName);
		BlockData GetBlockData(char blockType);
		ControlData GetControls(std::string charName);
		BaseBlock* GetCharLocation(MovingObjects* object);
		bool CheckCoordIfAvailable(int x, int y);
		BaseBlock* GetBlockAtCoord(int x, int y);

		std::vector<BaseBlock*> GetCurrentLevel() const;

		std::vector<MovingObjects*> GetGameObjects() const;
		void InsertGameObject(MovingObjects* object);
		void ClearDeadGameObjects();
		void ClearGameObjects();
		void AtEndOfGame();



	private:
		//variables
		bool running;
		SDL_Window* window;
		SDL_Renderer* renderer;
		int windowWidth, windowHeight;

		Menu menu;
		LevelHandler levelHandler;

		//containers for storing data about objects/levels
		std::vector<CharData> charData;
		std::vector<BlockData> blockData;
		std::vector<BaseBlock*> currentLevel;
		std::vector<MovingObjects*> gameObjects;
		std::vector<ControlData> controls;

};


#endif 