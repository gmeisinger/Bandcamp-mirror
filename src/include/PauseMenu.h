#ifndef BANDCAMP_PAUSEMENU_H_
#define BANDCAMP_PAUSEMENU_H_

#include <SDL.h>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <string>

#include "screen.h"

class PauseMenu : public Screen 
{ 
	private:
		bool start;
		std::unordered_map<std::string, Object*> objectList;
		SDL_Renderer* rendererReference;
		bool up, down, left, right, enter;
	public: 
		PauseMenu();
		void init(SDL_Renderer* renderer);
		void input(const Uint8* keystate);
		void update(Uint32 ticks);
		SDL_Renderer* draw(SDL_Renderer* renderer);
};

#endif  //  BANDCAMP_PAUSEMENU_H_