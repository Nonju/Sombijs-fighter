
#include <algorithm>

#include "game.h"
#include "block/baseblock.h"

using namespace std;

Game::Game()
:gameState{GameState::Menu}, running{true}, menu{this},
 levelHandler{this}, gameObjects{} {}

Game::~Game() {
	Clean();
}

void Game::Init(const char* title, int width, int height) {
	// initialize windowSizeVariables
	windowWidth = width;
	windowHeight = height;

	// initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO /*|SDL_INIT_AUDIO*/) != 0) {
		cerr << "Error initializing SDL" << endl;
		exit(1);
	}

	// create the window
	window = SDL_CreateWindow(title,SDL_WINDOWPOS_UNDEFINED,
	 SDL_WINDOWPOS_UNDEFINED, windowWidth,
	 windowHeight, SDL_WINDOW_RESIZABLE);
	
	//create renderer
	renderer = SDL_CreateRenderer(window, -1, 0);

	// make scaled rendering look smoother
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
	// render at a virtual resolution then stretch to actual resolution
	SDL_RenderSetLogicalSize(renderer, windowWidth, windowHeight);

	//load data about characters
	AttrLoader loader{};
	charData = loader.GetCharData(renderer, "assets/data/chardata.txt");
	blockData = loader.GetBlockData(renderer, "assets/data/blockdata.txt");
	controls = loader.GetControlData("assets/data/controls.txt");

	//load menu
	menu.Load(renderer);

	//load levelHandler
	levelHandler.Load(renderer);

	//load specified level from textfile
	currentLevel = levelHandler.LoadLevel("assets/levels/lvl1.txt",
	 windowWidth, windowHeight); //move to be done at menu instead

}

bool Game::StillRunning() { return running; }

void Game::EventHandler() {

	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) { 
			gameState = GameState::Quit;
		}
		else if (event.type == SDL_KEYDOWN) {
			if (event.key.keysym.sym == SDLK_ESCAPE) { 
				if (gameState != GameState::Menu) {
					gameState = GameState::Menu;
					AtEndOfGame();
				}
				/*else { //cant exit program with <escape>
					gameState = GameState::Quit;
				}*/
			}
		}
	}

}

const unsigned int frameDelay = 10;
unsigned int currentFrameDelay;
unsigned int startTime = SDL_GetTicks();
unsigned int lastTime = startTime;

bool runOnce{false};
void Game::Update() {

	//calculate time for updates
	currentFrameDelay = SDL_GetTicks() - lastTime;
	float currentTime = currentFrameDelay / 1000.0;
	lastTime += currentFrameDelay;

	//update according to current gamestate
	switch(gameState) {
		case GameState::SinglePlayer:
			//play-code
			levelHandler.SetNrOfPlayers(1);
			if (levelHandler.Update(currentTime)) {
				gameState = GameState::Menu;
				AtEndOfGame();
			}
			break;

		case GameState::MultiPlayer:
			//play-code
			levelHandler.SetNrOfPlayers(2);
			if (levelHandler.Update(currentTime)) {
				gameState = GameState::Menu;
				AtEndOfGame();
			}
			break;

		case GameState::Quit:
			Quit();
			break;

		case GameState::Menu:
		default:
			//menu-code
			menu.Update();
			break;
			
	}
}

void Game::Draw() {
	// clear screen
	SDL_SetRenderDrawColor(renderer, 120, 120, 120, 255);
	SDL_RenderClear(renderer);

	// draw things
	switch(gameState) {
		//singleplayer/multiplayer has same draws
		case GameState::SinglePlayer:
		case GameState::MultiPlayer:
			//draw play-images
			levelHandler.Draw(renderer);
			for (MovingObjects* mo : gameObjects) {
				mo->Draw(renderer);
			}
			break;

		case GameState::Menu:
		default:
			menu.Draw(renderer);
			break;

	}

	// show the newly drawn things
	SDL_RenderPresent(renderer);

	// wait before drawing the next frame
	currentFrameDelay = SDL_GetTicks() - lastTime;
	if (frameDelay > currentFrameDelay) {
		// only wait if it's actually needed
		unsigned int sleepTime = frameDelay - currentFrameDelay;
		//cout << "SLEEP: " << sleepTime << endl;
		SDL_Delay(sleepTime);
	}
}

void Game::Clean() {
	//clean allocated assets and more, then quit
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	for (BaseBlock* bb : currentLevel) { delete bb; }
	for (MovingObjects* mo : gameObjects) { delete mo; }
	for (CharData cd : charData) { SDL_DestroyTexture(cd.texture); }
	for (BlockData bd : blockData) { SDL_DestroyTexture(bd.texture); }


	SDL_Quit();
}

void Game::Quit() { running = false; }


//Data functions

int Game::GetWindowWidth() const { return windowWidth; }
int Game::GetWindowHeight() const { return windowHeight; }

CharData Game::GetCharData(string charName) {
	//gets data about a specified characters
	for (CharData cd : charData) {
		if (cd.charName == charName) { return cd; }
	}
	return charData.at(0); //if not found
}

BlockData Game::GetBlockData(string blockName) {
	for (BlockData bd : blockData) {
		if (bd.blockName == blockName) { return bd; }
	}
	return blockData.at(0); //if not found
}

BlockData Game::GetBlockData(char blockType) {
	for (BlockData bd : blockData) {
		if (bd.blockType == blockType) { return bd; }
	}
	return blockData.at(0); //if not found
}

ControlData Game::GetControls(string charName) {
	for (ControlData cd : controls) {
		if (cd.charName == charName) { return cd; }
	}
	return controls.at(0); //if not found
}

BaseBlock* Game::GetCharLocation(MovingObjects* object) {
	int objectX{object->GetCenterX()};
	int objectY{object->GetCenterY()};

	for (BaseBlock* bb : currentLevel) {
		//used more than once --> stored in variable
		int blockX{bb->GetX()};
		int blockY{bb->GetY()};

		if (objectX > blockX &&
		 objectX <= (blockX + bb->GetWidth()) &&
		 objectY > blockY &&
		 objectY <= (blockY + bb->GetHeight())) {
			return bb;
		}
	}

	//couldn't find target --> returning first bloc
	return currentLevel.at(0);
}

bool Game::CheckCoordIfAvailable(int x, int y) {
	for (BaseBlock* bb : currentLevel) {
		if (bb->GetCoordX() == x &&
			bb->GetCoordY() == y) { 
			return bb->CanIntersect();
		}
	}
	return true;
}

BaseBlock* Game::GetBlockAtCoord(int x, int y) {

	return *find_if(currentLevel.begin(), currentLevel.end(),
	 [x, y](BaseBlock* a)->bool {
		return a->GetCoordX() == x && a->GetCoordY() == y;
	});

	return nullptr;
}

vector<BaseBlock*> Game::GetCurrentLevel() const {
	return currentLevel;
}

vector<MovingObjects*> Game::GetGameObjects() const {
	return gameObjects;
}

void Game::InsertGameObject(MovingObjects* object) {
	gameObjects.push_back(object);
}

void Game::ClearDeadGameObjects() {
	//check for dead objects and then delete them
	for (MovingObjects* &mo : gameObjects) {
		if (!mo->IsAlive()) { 
			delete mo;
			mo = nullptr;
		}
	}

	//clear list from dead pointers
	gameObjects.erase(remove(gameObjects.begin(), gameObjects.end(), nullptr),
	gameObjects.end());
}

void Game::ClearGameObjects() {
	if (!gameObjects.empty()) {
		for (MovingObjects* mo : gameObjects) { 
			delete mo; 
			mo = nullptr;
		}
		//clear list from dead pointers
		gameObjects.clear();
	}
}

void Game::AtEndOfGame() {
	levelHandler.Reset();
	menu.Reset();
}
