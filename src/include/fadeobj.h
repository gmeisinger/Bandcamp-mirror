#ifndef BANDCAMP_FADEOBJ_H_
#define BANDCAMP_FADEOBJ_H_

#include <vector>
#include <unordered_map>
#include <SDL.h>
#include <string>
#include <algorithm>
#include <sstream>
#include <iostream>

#include "object.h"
#include "game.h"

class FadeObj : public Object
{
	private:
		bool fadeIn; // Fading In or Out?    T - FadeIN   F - FadeOUT
		int currentTick; //For updating the alpha value
		int dest; // Which room do you go to after the fade?
		int currentFade; //What alpha should it be at currently?
		SDL_Rect fullScreen;
		bool done; //Has it finished fading?

	public:
		void input(const Uint8* keystate);
		void init(SDL_Renderer *renderer);
		void update(std::unordered_map<std::string, Object*> &objectList, std::vector<std::vector<Tile*>> &grid, Uint32 ticks);
		std::string getInstanceName();
		SDL_Renderer* draw(SDL_Renderer *renderer, SDL_Rect cam);
		bool isUsed();
		bool isFadeIn();
		int getDest();
		FadeObj();
        ~FadeObj();
		FadeObj(int dest);
};

#endif  //  BANDCAMP_FADEOBJ_H_