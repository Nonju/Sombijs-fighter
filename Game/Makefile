
#File for simpler compile of project

CC = g++
CFLAGS = -std=c++11 -pedantic -Wall -Wextra -Wno-unused-parameter -c -g
SDL_FLAGS = `sdl2-config --libs --cflags` -lSDL2_image -lSDL2_ttf

all: Sombijs_fighter


#player enemy
Sombijs_fighter: main game menu.o polly.o tools blocks levelhandler.o characters.o
	$(CC) *.o $(SDL_FLAGS) -o Sombijs_fighter && make clean && make run

#for when you dont want game to auto start on compile
just_compile: main game menu.o polly.o tools blocks levelhandler.o characters.o
	$(CC) *.o $(SDL_FLAGS) -o Sombijs_fighter

main: main.cc
	$(CC) $(CFLAGS) main.cc

menu.o: menu/imageobjects.cc menu/menu.cc
	$(CC) $(CFLAGS) menu/imageobjects.cc menu/menu.cc

game: game.cc
	$(CC) $(CFLAGS) game.cc

levelhandler.o: levelhandler/levelhandler.cc
	$(CC) $(CFLAGS) levelhandler/levelhandler.cc

polly.o: polly/objects.cc polly/physicalobjects.cc polly/movingobjects.cc
	$(CC) $(CFLAGS) polly/objects.cc polly/physicalobjects.cc polly/movingobjects.cc

tools: gametools/attrloader.cc gametools/levelloader.cc gametools/createtexture.cc
	$(CC) $(CFLAGS) gametools/attrloader.cc gametools/levelloader.cc gametools/createtexture.cc

blocks: block/baseblock.cc block/blocks.cc
	$(CC) $(CFLAGS)	block/baseblock.cc block/blocks.cc

characters.o: characters/character.cc characters/player.cc characters/bullet.cc characters/enemy.cc
	$(CC) $(CFLAGS) characters/character.cc characters/player.cc characters/bullet.cc characters/enemy.cc


clean:
	rm -rf *.o

full_clean:
	make clean && rm Sombijs_fighter

run: 
	./Sombijs_fighter
