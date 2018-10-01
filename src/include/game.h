#ifndef BANDCAMP_GAME_H_
#define BANDCAMP_GAME_H_

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <vector>
#include <string>
#include "credits.h"

class Game
{
private:
	bool running;
	//bool isPaused;
	//current map
	//current room
	//vectors for:
	//	enemies
	//	items
	SDL_Window* gWindow;
	SDL_Surface* gScreenSurface;
	SDL_Renderer* gRenderer;
public:
	//extern constexpr int TILE_SIZE;
	Game();
	//~Game();
	bool init();
	void run();
	void close();
	//void input();
	void update();
	void draw();
	//static SDL_Texture* loadTexture(std::string fname);

};
#endif	//	BANDCAMP_GAME_H_