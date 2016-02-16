
#include "blocks.h"
#include "../gametools/datacontainers.h"
#include "../characters/player.h"
#include "../characters/enemy.h"
//#include "../powerup/powerup.h" //fixa senare


using namespace std;

//---------------EMTYBLOCK---------------

EmptyBlock::EmptyBlock(SDL_Texture* texture, int posX, int posY,
		 int width, int height, bool passable)
		: BaseBlock(texture, posX, posY, width, height, passable) {}

EmptyBlock::EmptyBlock(SDL_Texture* texture, int posX, int posY,
		 int width, int height)
		: EmptyBlock(texture, posX, posY, width, height, true) {}

EmptyBlock::EmptyBlock(Game* game, char blockType, int posX, int posY)
		: BaseBlock(game, blockType, posX, posY) {}


//------------------WALL-----------------

WallBlock::WallBlock(SDL_Texture* texture, int posX, int posY,
		 int width, int height, bool passable)
		: BaseBlock(texture, posX, posY, width, height, passable) {}

WallBlock::WallBlock(SDL_Texture* texture, int posX, int posY,
		 int width, int height)
		: WallBlock(texture, posX, posY, width, height, false) {}

WallBlock::WallBlock(Game* game, char blockType, int posX, int posY)
		: BaseBlock(game, blockType, posX, posY) {}


//----------------SPAWNER----------------

Spawner::Spawner(SDL_Texture* texture, int posX, int posY,
		 int width, int height, bool passable)
		: BaseBlock(texture, posX, posY, width, height, passable) {}

Spawner::Spawner(SDL_Texture* texture, int posX, int posY,
		 int width, int height)
		: Spawner(texture, posX, posY, width, height, true) {}

Spawner::Spawner(Game* game, char blockType, int posX, int posY)
		: BaseBlock(game, blockType, posX, posY) { }


//--------------PLAYERSPAWN--------------

PlayerSpawn::PlayerSpawn(SDL_Texture* texture, int posX, int posY,
		 int width, int height, bool passable)
		: Spawner(texture, posX, posY, width, height, passable) {}

PlayerSpawn::PlayerSpawn(SDL_Texture* texture, int posX, int posY,
		 int width, int height)
		: PlayerSpawn(texture, posX, posY, width, height, true) {}

PlayerSpawn::PlayerSpawn(Game* game, char blockType, int posX, int posY)
		: Spawner(game, blockType, posX, posY) { }


void PlayerSpawn::Spawn(Game* game, int charHitPoints, int charNr) {

	BlockData data = game->GetBlockData(blockType);
	string player{(data.charName + to_string(charNr))};
	//Player* tmpPlayer{new Player{game, data.charName, GetX(), GetY()}};
	Player* tmpPlayer{new Player{game, player, GetX(), GetY()}};

	//set dynamic player values
	tmpPlayer->SetWidth(GetWidth() * 0.8);
	tmpPlayer->SetHeight(GetHeight() * 1);
	tmpPlayer->SetHitPoints(charHitPoints);
	tmpPlayer->SetCenterX(GetCenterX());
	tmpPlayer->SetCenterY(GetCenterY());

	//set player controls
	ControlData controls = game->GetControls(player);
	tmpPlayer->SetControlUp(controls.up);
	tmpPlayer->SetControlDown(controls.down);
	tmpPlayer->SetControlLeft(controls.left);
	tmpPlayer->SetControlRight(controls.right);
	tmpPlayer->SetControlShoot(controls.shoot);
	tmpPlayer->SetControlSpecial(controls.special);

	//insert new player into game's object container
	game->InsertGameObject(tmpPlayer);
	tmpPlayer = nullptr;
}

//--------------ENEMYSPAWN--------------

EnemySpawn::EnemySpawn(SDL_Texture* texture, int posX, int posY,
		 int width, int height, bool passable)
		: Spawner(texture, posX, posY, width, height, passable) {}

EnemySpawn::EnemySpawn(SDL_Texture* texture, int posX, int posY,
		 int width, int height)
		: Spawner(texture, posX, posY, width, height, true) {}

EnemySpawn::EnemySpawn(Game* game, char blockType, int posX, int posY)
		: Spawner(game, blockType, posX, posY) {}


void EnemySpawn::Spawn(Game* game, int charHitPoints, int charNr) {
	BlockData data = game->GetBlockData(blockType);
	Enemy* tmpEnemy{new Enemy{game, data.charName, GetX(), GetY()}};

	//find target player
	for (MovingObjects* mo : game->GetGameObjects()) {
		Player* player{dynamic_cast<Player*>(mo)};
		if (player != nullptr) {
			tmpEnemy->AddTarget(mo);
		}
	}

	tmpEnemy->SetCenterX(GetCenterX());
	tmpEnemy->SetCenterY(GetCenterY());

	tmpEnemy->SetWidth(GetWidth() * 0.6);
	tmpEnemy->SetHeight(GetHeight() * 0.7);
	tmpEnemy->SetHitPoints(charHitPoints);

	game->InsertGameObject(tmpEnemy);
	tmpEnemy = nullptr;
}


//--------------POWERUPSPAWN--------------

PowerupSpawn::PowerupSpawn(SDL_Texture* texture, int posX, int posY,
		 int width, int height, bool passable)
		: Spawner(texture, posX, posY, width, height, passable) {}

PowerupSpawn::PowerupSpawn(SDL_Texture* texture, int posX, int posY,
		 int width, int height)
		: PowerupSpawn(texture, posX, posY, width, height, true) {}

PowerupSpawn::PowerupSpawn(Game* game, char blockType, int posX, int posY)
		: Spawner(game, blockType, posX, posY) {}

void PowerupSpawn::Spawn(Game* game, int charHitPoints, int charNr) {
	//code for spawning powerups
}

