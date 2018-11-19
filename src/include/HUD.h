#ifndef BANDCAMP_HUD_H_
#define BANDCAMP_HUD_H_

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <SDL.h>
#include <SDL_image.h>
#include <algorithm>

#include "utils.h"
#include "object.h"
#include "global.h"

//initialize the HUD
class HUD : public Object
{
	public:
		HUD();
		~HUD();
		void init(SDL_Renderer* _renderer);
		void update(std::unordered_map<std::string, Object*> *objectList, std::vector<std::vector<Tile*>> grid, Uint32 ticks);
		void input(const Uint8* keystate);
		SDL_Renderer* change_levels(SDL_Renderer* _renderer, int oxygen_level, int temperature_level, int health_level); // int power_level) can add for power 
		SDL_Renderer* draw(SDL_Renderer* gRenderer, SDL_Rect cam);
		int currentTemp;
		int currentOxygen;
		int currentHealth;
		bool isUsed();
	private:
		bool init_h;
		std::vector<SDL_Texture*> hud;
		SDL_Renderer* renderer_h;
		SDL_Rect Temp;
		SDL_Rect Oxygen;
		std::string getInstanceName();
};

#endif  //  BANDCAMP_HUD_H_
