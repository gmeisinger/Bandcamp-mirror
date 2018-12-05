#ifndef BANDCAMP_GAME_H_
#define BANDCAMP_GAME_H_

#include <SDL.h>
#include <iostream>
#include <vector>
#include <string>
#include "credits.h"
#include "GSM.h"

class GSM;

//extern int SCREEN_WIDTH;
//extern int SCREEN_HEIGHT;
//extern int TILE_SIZE;

class Game {
	private:
		bool running;
		SDL_Window* gWindow;
		SDL_Renderer* gRenderer;
		GSM * gsm;
	public:
		Game();
		//~Game();
		bool init();
		void run();
		void close();
		void change_track();
		void input(const Uint8* keystate);
		void update(Uint32 ticks);
		void draw();
};
#endif	//	BANDCAMP_GAME_H_
