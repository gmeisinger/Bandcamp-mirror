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
		void lower_oxygen();
		void raise_oxygen(int resource_value);
		void lower_temperature();
		void raise_temperature(int resource_value);
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