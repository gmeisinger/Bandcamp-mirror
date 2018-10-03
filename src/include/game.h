#ifndef BANDCAMP_GAME_H_
#define BANDCAMP_GAME_H_

#include <SDL.h>
#include <iostream>
#include <vector>
#include <string>
#include "credits.h"
#include "sprite.h"
#include "GSM.h"

	extern int screen_w;
	extern int screen_h;
	extern int tile_s;

class Game {
	private:
		bool running;
		SDL_Window* gWindow;
		SDL_Renderer* gRenderer;
		GSM gsm;
	public:
		Game();
		//~Game();
		bool init();
		void run();
		void close();
		void input(const Uint8* keystate);
		void update();
		void draw();
};
#endif	//	BANDCAMP_GAME_H_