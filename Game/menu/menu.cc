
#include <iostream>

#include <fstream>
#include <algorithm>
#include <cctype>

#include "menu.h"
#include "../game.h"
#include "../gametools/createtexture.h"

using namespace std;

Menu::Menu(Game* gamePointer)
	:game{gamePointer} {

		if (TTF_Init() < 0) {
			cerr << "TTF could not be initialized!" << endl;
		}
	}

Menu::~Menu() {
	TTF_CloseFont(highScoreFont);
	TTF_Quit();
}

void Menu::Load(SDL_Renderer* renderer) {
	CreateTexture ct{};
	SDL_Texture* tmpTexture{nullptr};
	SDL_Rect tmpRect;

	//general values
	int windowWidth{game->GetWindowWidth()};
	int windowHeight{game->GetWindowHeight()};
	int menuAlternativeX{static_cast<int>(windowWidth * 0.1)};


	tmpRect.w = windowWidth * 0.6;
	tmpRect.h = windowHeight * 0.1;

	//header
	tmpTexture = ct.GetTexture(renderer,
	 "assets/images/Header.png");
	tmpRect.x = windowWidth * 0.2;
	tmpRect.y = windowHeight * 0.2;
	menuText.insert(make_pair(tmpTexture, tmpRect));

	//singleplayer
	tmpTexture = ct.GetTexture(renderer,
	 "assets/images/SinglePlayerNoDrama.png");
	tmpRect.x = menuAlternativeX;
	tmpRect.y = windowHeight * 0.5;
	menuText.insert(make_pair(tmpTexture, tmpRect));

	//multiplayer
	tmpTexture = ct.GetTexture(renderer,
	 "assets/images/MultiPlayerDrama.png");
	tmpRect.x = menuAlternativeX;
	tmpRect.y = windowHeight * 0.6;
	menuText.insert(make_pair(tmpTexture, tmpRect));

	//quit
	tmpTexture = ct.GetTexture(renderer,
	 "assets/images/Quit2.png");
	tmpRect.x = menuAlternativeX;
	tmpRect.y = windowHeight * 0.7;
	menuText.insert(make_pair(tmpTexture, tmpRect));

	//highscores
	hsPosX = windowWidth * 0.8;
	hsPosY = windowHeight * 0.45;

	//set font (address from main-folder)
	highScoreFont = TTF_OpenFont("assets/fonts/Top_Secret.ttf", 30);

	//read highscores from textfile
	ReadHighScores("assets/data/highscores.txt");

}

void Menu::Update() {
	//READ KEYBOARD INPUT

	//read keyboardstate
	const Uint8 *state = SDL_GetKeyboardState(NULL);

	if (state[SDL_SCANCODE_1]) { //singleplayer
		game->gameState = Game::GameState::SinglePlayer;
	}
	else if (state[SDL_SCANCODE_2]) { //multiplayer
		game->gameState = Game::GameState::MultiPlayer;
	}
	else if (state[SDL_SCANCODE_5]) { //quit
		game->gameState = Game::GameState::Quit;
	}
}

void Menu::Draw(SDL_Renderer* renderer) {
	for (map<SDL_Texture*, SDL_Rect>::const_iterator it{menuText.begin()};
			it != menuText.end(); ++it) {
		SDL_RenderCopy(renderer, it->first, nullptr, &it->second);
	}

	PrintHighScores(renderer);
}

void Menu::Reset() {
	ReadHighScores("assets/data/highscores.txt");
}

string Menu::SplitLine(string const& line) const {
	long unsigned int pos{line.find(" ")};
	if (pos != string::npos) {
		return line.substr(0, pos);
	}
	else { return line; }
}

void Menu::ReadHighScores(string filename) {
	//clear old highScores
	if (highScores.size() != 0) {
		highScores.clear();
	}

	ifstream ifs{filename};

	if (!ifs) {
		cerr << "File (" << filename << ") could not be opened!" << endl;
	}
	else {
		//first retreive all data from file
		string line{};
		while (getline(ifs, line)) {
			string tmpString{SplitLine(line)};
			if (!line.empty()) { //ignore empty lines
				highScores.push_back(tmpString);	
			}
		}

		//then sort vector after largest numerical value
		sort(highScores.begin(), highScores.end(),
			[](string const& a, string const& b)->bool{
				return stoi(a) > stoi(b);
		});
		string headerText{"Highscores!"};
		//highScores.insert(highScores.begin(), " ");
		highScores.insert(highScores.begin(), string(headerText.size(), ' '));
		highScores.insert(highScores.begin(), headerText);

	}

}

void Menu::PrintHighScores(SDL_Renderer* renderer) {
	//flytta runt variabler osv till bättre platser senare

	SDL_Color fontColor = {255,255,255,255};
	SDL_Surface* fontSurface;
	SDL_Texture* fontTexture;
	SDL_Rect fontRect;

	fontRect.x = hsPosX;
	int lineCounter{0};
	for (string hs : highScores) {
		if (lineCounter >= 12) { break; } //only use top 10 scores

		string hsLine{};
		if (lineCounter != 0 && lineCounter != 1) {
			hsLine = to_string(lineCounter-1) + ": " + hs;
		}
		else {
			hsLine = hs;
		}
		fontSurface = TTF_RenderText_Solid(highScoreFont,
			 hsLine.c_str(), fontColor);	
		fontTexture = SDL_CreateTextureFromSurface(renderer, fontSurface);
		SDL_FreeSurface(fontSurface);

		SDL_QueryTexture(fontTexture, nullptr, nullptr,
		 &fontRect.w, &fontRect.h);
		fontRect.y = hsPosY + (fontRect.h * lineCounter++);

		SDL_RenderCopy(renderer, fontTexture, nullptr, &fontRect);
		SDL_DestroyTexture(fontTexture);

	}
}

