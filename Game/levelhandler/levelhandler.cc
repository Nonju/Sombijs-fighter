
#include <algorithm>
#include <cctype>
#include <sstream>
#include <fstream>

#include "levelhandler.h"
#include "../game.h"
#include "../block/baseblock.h"
#include "../block/blocks.h"
#include "../characters/character.h"
#include "../characters/player.h"
#include "../characters/enemy.h"
#include "../characters/bullet.h"


using namespace std;

LevelHandler::LevelHandler(Game* gamePointer)
	: game{gamePointer}, score{0}, playerBaseHP{10},
	 playerCurrentHP{playerBaseHP}, enemyBaseHP{3},
	 passedTime{0}, spawnPlayer{true}, spawnEnemy{false},
	 baseNrOfEnemies{15}, maxNrOfEnemies{baseNrOfEnemies},
	 difficultyRiseTimer{10}, timeSinceDiffRise{0},
	 enemySpawnTime{5}, timeSinceEnemySpawn{0},
	 powerupSpawnTime{30}, timeSincePowerupSpawn{0} {

 	if (TTF_Init() < 0) {
 		cerr << "TTF could not be initialized!" << endl;
 	}

 	//set font (address from main-folder)
	textFont = TTF_OpenFont("assets/fonts/Top_Secret.ttf", 30);
	fontColor = {255,255,255,255};
 }

LevelHandler::~LevelHandler() {
	TTF_CloseFont(textFont);
	TTF_Quit();
}

void LevelHandler::Load(SDL_Renderer* renderer) {

	//general values
	int windowWidth{game->GetWindowWidth()};
	int windowHeight{game->GetWindowHeight()};
	int textWidth{static_cast<int>(windowWidth * 0.4)};
	int textHeight{static_cast<int>(windowHeight * 0.1)};
	int textPosY{static_cast<int>(windowHeight * 0.01)};

	//hitpoints
	hpRect.x = windowWidth * 0.01;
	hpRect.y = textPosY;
	hpRect.w = textWidth;
	hpRect.h = textHeight;

	//score
	scoreRect.x = windowWidth * 0.5;
	scoreRect.y = textPosY;
	scoreRect.w = textWidth;
	scoreRect.h = textHeight;

}

bool LevelHandler::CheckIfGameOver() {
	return playerCurrentHP <= 0;
}


bool LevelHandler::Update(float currentTime) {
	passedTime += currentTime;

	if ((passedTime - timeSinceDiffRise) >= difficultyRiseTimer) {
		timeSinceDiffRise = passedTime;
		maxNrOfEnemies++;
		enemySpawnTime *= 0.9;
	}

	//check if spawners should spawn more enemies
	if ((passedTime - timeSinceEnemySpawn) >= enemySpawnTime) {
		timeSinceEnemySpawn = passedTime;
		spawnEnemy = true;
	}
	else { spawnEnemy = false; }

	for (BaseBlock* bb : game->GetCurrentLevel()) {

		if (spawnPlayer && PlayerCount() < nrOfPlayers) {
			PlayerSpawn* PS{dynamic_cast<PlayerSpawn*>(bb)};
			if (PS != nullptr && spawnPlayer) {
				PS->Spawn(game, playerBaseHP, PlayerCount()+1);
				continue;
			}
		}

		if (spawnEnemy && EnemyCount() < maxNrOfEnemies) {
			EnemySpawn* ES{dynamic_cast<EnemySpawn*>(bb)};
			if (ES != nullptr) {
				ES->Spawn(game, enemyBaseHP);
				continue;
			}
		}
	}
	if (spawnPlayer) { spawnPlayer = false; }

	for (MovingObjects* mo : game->GetGameObjects()) {
		Character* character{dynamic_cast<Character*>(mo)};
		if (character != nullptr) {
			character->Update(passedTime, game);
		}
		else {
			mo->Update(currentTime);
		}
		
	}

	CheckForCollisions();

	if (CheckIfGameOver()) {
		if (score != 0) {
			InsertHighScore("assets/data/highscores.txt");
		}
		Reset();
		return true;
	}
	return false;
}

void LevelHandler::Draw(SDL_Renderer* renderer) {

	if (nrOfPlayers == 1) {
		//text -- hitpoints -- 1 player
		string hpString{"HP: " + to_string(playerCurrentHP)};
		TextPrinter(renderer, hpRect, hpString);
	}

	//text -- hitpoints -- 2 players
	if (nrOfPlayers == 2) {
		string hpString{"Combined HP: " + to_string(playerCurrentHP)};
		TextPrinter(renderer, hpRect, hpString);	
	}
	

	//text -- score
	string scoreString{"Score: " + to_string(score)};
	TextPrinter(renderer, scoreRect, scoreString);
	
	
	//blocks
	for (BaseBlock* bb : game->GetCurrentLevel()) {
		bb->Draw(renderer);
	}

	//objects
	for (MovingObjects* mo : game->GetGameObjects()) {
		mo->Draw(renderer);
	}
}

//void LevelHandler::LoadLevel(string levelName,
vector<BaseBlock*> LevelHandler::LoadLevel(string levelName,
 int windowWidth, int windowHeight) {

	vector<BaseBlock*> currentLevel;

	//refill with new levelData
	LevelLoader lvlLoader{};
	currentLevel = lvlLoader.LoadLevel(game, levelName);

	//calculate dynamic width/height for blocks
	//then reset each blocks standard width/height
	int xBlocks{0}, yBlocks{0};
	for_each(currentLevel.begin(), currentLevel.end(),
	 [&xBlocks, &yBlocks](BaseBlock* const& a)->void{
	 	if (a->GetCoordX() > xBlocks) { xBlocks = a->GetCoordX(); }
	 	if (a->GetCoordY() > yBlocks) { yBlocks = a->GetCoordY(); }
	 });

	int sizeMax{};
	if (xBlocks > 0 && yBlocks > 0) {
		sizeMax = min(windowWidth, windowHeight) / max(xBlocks, yBlocks)+1;
	}
	else {
		sizeMax = max(currentLevel.at(0)->GetWidth(), 
			currentLevel.at(0)->GetHeight());
	}

	for (BaseBlock* bb : currentLevel) {
		bb->SetWidth(sizeMax);
		bb->SetHeight(sizeMax);
		
		bb->SetX(10 + (bb->GetCoordX() * bb->GetWidth()));
		bb->SetY(40 + (bb->GetCoordY() * bb->GetHeight()));
	}

	return currentLevel;
	
}

int LevelHandler::EnemyCount() const {
	int counter{0};

	for (MovingObjects* mo : game->GetGameObjects()) {
		Enemy* enemy{dynamic_cast<Enemy*>(mo)};
		if (enemy != nullptr) {
			counter++;
		}
	}
	return counter;
}

int LevelHandler::PlayerCount() const {
	int counter{0};

	for (MovingObjects* mo : game->GetGameObjects()) {
		Player* player{dynamic_cast<Player*>(mo)};
		if (player != nullptr) {
			counter++;
		}
	}
	return counter;	
}

void LevelHandler::SetNrOfPlayers(int nr) {
	nrOfPlayers = nr;
}

void LevelHandler::Reset() {
	//clear gameobjects from previous sessions

	playerCurrentHP = playerBaseHP;
	score = 0;

	maxNrOfEnemies = baseNrOfEnemies;

	game->ClearGameObjects();
	spawnPlayer = true;
}

void LevelHandler::CheckForCollisions() {
	
	for (MovingObjects* mo1 : game->GetGameObjects()) {
		for (MovingObjects* mo2 : game->GetGameObjects()) {

			//player/enemy collision
			Player* player{dynamic_cast<Player*>(mo1)};
			Enemy* enemy{dynamic_cast<Enemy*>(mo2)};
			if (player != nullptr && enemy != nullptr) {
				if (player->CollisionDetection(enemy) &&
					enemy->IsAlive()) {

					--playerCurrentHP;
					enemy->SetIsAlive(false);
					continue;
				}
			}

			//enemy/bullet collision
			Bullet* bullet{dynamic_cast<Bullet*>(mo1)};
			if (bullet != nullptr && enemy != nullptr) {
				if (bullet->CollisionDetection(enemy)) {
					bullet->SetIsAlive(false);
					enemy->SetHitPoints(
						enemy->GetHitPoints() - bullet->GetDamage());
					score++;
					continue;
				}
			}

			//bullet/wall (???)
			if (bullet != nullptr) {
				for (BaseBlock* bb : game->GetCurrentLevel()) {
					if (bullet->CollisionDetection(bb)) {
						bullet->SetIsAlive(false);
						continue;
					}
				}
			}


		}
	}

	//clear dead objects
	game->ClearDeadGameObjects();

}

void LevelHandler::InsertHighScore(string filename) {
	//save old data from file
	vector<string> fileContent;
	ifstream ifs{filename};
	if (!ifs) {
		cerr << "File (" << filename << ") could not be opened!" << endl;
	}
	else {
		string line{};
		while (getline(ifs, line)) {
			fileContent.push_back(line);
		}
	}
	ifs.close();

	//insert new data back into file
	ofstream ofs{filename};
	if (!ofs) {
		cerr << "File (" << filename << ") could not be opened!" << endl;
	}
	else {
		for (string s : fileContent) { ofs << s << endl; }
		ofs << to_string(score) << endl; //add new data
	}
}

void LevelHandler::TextPrinter(SDL_Renderer* renderer, SDL_Rect rect, string text) {
	//flytta runt variabler osv till bättre platser senare

	SDL_Surface* fontSurface;
	SDL_Texture* fontTexture;

	fontSurface = TTF_RenderText_Solid(textFont,
		 text.c_str(), fontColor);	
	fontTexture = SDL_CreateTextureFromSurface(renderer, fontSurface);
	SDL_FreeSurface(fontSurface);

	SDL_QueryTexture(fontTexture, nullptr, nullptr,
	 &rect.w, &rect.h);

	SDL_RenderCopy(renderer, fontTexture, nullptr, &rect);
	SDL_DestroyTexture(fontTexture);

}

