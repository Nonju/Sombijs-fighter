#ifndef LEVELLOADER_H
#define LEVELLOADER_H


#include <vector>

#include "../block/baseblock.h"
#include "../block/blocks.h"

class Game;

class LevelLoader {

	public:
		LevelLoader();
		std::vector<BaseBlock*> LoadLevel(Game* game, std::string filepath);
		std::vector<std::string> GetLevels(std::string filepath) = delete;

	private:
		BaseBlock* BlockParser(Game* game, char blockType, int posX, int posY);
};

#endif