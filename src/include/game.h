#ifndef BANDCAMP_GAME_H_
#define BANDCAMP_GAME_H_

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <vector>
#include <string>
#include "credits.h"
#include "sprite.h"

class Game
{
private:
	bool running;
	SDL_Window* gWindow;
	SDL_Renderer* gRenderer;
	std::vector<Sprite> sprites;
public:
	Game();
	//~Game();
	bool init();
	void loadMedia();
	void run();
	void close();
	void updatePlayer();
	//void input();
	void update();
	void draw();

};
#endif	//	BANDCAMP_GAME_H_