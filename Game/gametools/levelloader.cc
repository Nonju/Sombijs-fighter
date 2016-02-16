#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>


#include "levelloader.h"
#include "../game.h"
//#include "../block/baseblock.h"
//#include "../block/blocks.h"

using namespace std;

LevelLoader::LevelLoader() {}

BaseBlock* LevelLoader::BlockParser(Game* game, char blockType,
 int posX, int posY) {
	//find out what block is to be created
	BaseBlock* tmp{nullptr};
	switch (blockType) {
		case '#': //hard wall
			tmp = new WallBlock{game, blockType, posX, posY};
			break;

		case '+': //destructable wall
			tmp = new WallBlock{game, blockType, posX, posY};
			break;

		case 'x': //enemyspawner
			tmp = new EnemySpawn{game, blockType, posX, posY};
			break;

		case 'o': //playerspawn
			tmp = new PlayerSpawn{game, blockType, posX, posY};
			break;

		case 'u': //powerupspawner
			tmp = new PowerupSpawn{game, blockType, posX, posY};
			break;

		case '.': //floor -- default
		default:
			tmp = new EmptyBlock{game, blockType, posX, posY};
			break;
	}
	
	tmp->SetCoordX(posX);
	tmp->SetCoordY(posY);

	return tmp;
}

vector<BaseBlock*> LevelLoader::LoadLevel(Game* game, string filepath) {

	vector<BaseBlock*> level;
	ifstream ifs{filepath};
	if (!ifs) {
		cerr << "File (" << filepath << ") could not be opened!" << endl;
	}
	else {
		string line{};
		int y{0};
		while (getline(ifs, line)) {
			if (line.size() > 0 && line.find("//") != 0) {

				cout << "LEVEL: " << line << endl;
				for (unsigned int x{0}; x < line.size(); ++x) {
					level.push_back(BlockParser(game, line.at(x), x, y));
				}
				y++; //move on to next row
			}
		}
	}
	return level;
}

#if 0
vector<string> LevelLoader::GetLevels(string filepath) {
	/*
	få ut alla textfilers namn 
	från ../assets/levels/
	Implementera senare!!
	*/
	vector<string> levels;

	return levels;
}
#endif

