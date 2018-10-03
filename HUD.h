#ifndef BANDCAMP_HUD_H_
#define BANDCAMP_HUD_H_

#include <iostream>
#include <string>
#include <vector>
#include <SDL.h>
#include <SDL_image.h>
#include "utils.h"

//initialize the HUD
class HUD
{
	public:
		void init_HUD();
		void change_levels(int oxygen_level, int temperature_level);
		void set_renderer(SDL_Renderer* _renderer);
		HUD(SDL_Renderer* _gRenderer);
		~HUD();
	private:
		bool init_h;
		std::vector<SDL_Texture*> hud;
		SDL_Renderer* renderer_h;
		SDL_Rect Temp;
		SDL_Rect Oxygen;
};

#endif  //  BANDCAMP_HUD_H_