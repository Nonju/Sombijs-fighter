#ifndef MENU_H
#define MENU_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <vector>
#include <map>
#include <string>

#include "imageobjects.h"

class Game;

class Menu {

	public:
		Menu(Game* gamePointer);
		~Menu();

		void Load(SDL_Renderer* renderer);
		void Update();
		void Draw(SDL_Renderer* renderer);
		void Reset();

	private:
		//variables
		Game* game;
		std::map<SDL_Texture*, SDL_Rect> menuText;

		//highscores
		std::vector<std::string> highScores;
		TTF_Font* highScoreFont;
		int hsPosX, hsPosY; //highscore-base-position


		//functions
		std::string SplitLine(std::string const& line) const;
		void ReadHighScores(std::string filename);
		void PrintHighScores(SDL_Renderer* renderer);

};


#endif