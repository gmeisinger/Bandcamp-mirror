#ifndef BANDCAMP_PICKUP_H_
#define BANDCAMP_PICKUP_H_

#include <vector>
#include <unordered_map>
#include <SDL.h>
#include "player.h"
#include "HUD.h"
#include "object.h"

#include "ooze.h"

#include <string>
#include <algorithm>

#include "physics.h"

#include "utils.h"
#include "randommap.h"

#include <sstream>
#include <iostream>

class Player;

class Pickup : public Object
{
	private:
		SDL_Rect pickupRect;
		SDL_Rect drawBox;
		char pickupType;
		int pickupValue;
		Player *pickupPlayer;
		HUD *hud;
		bool up;			//Is the image floating up or down.

	public:
		//static int totalInstance;
		void input(const Uint8* keystate);
		void init(SDL_Renderer *renderer);
		void update(std::unordered_map<std::string, Object*> *objectList, std::vector<std::vector<Tile*>> grid, Uint32 ticks);
		std::string getInstanceName();
		SDL_Renderer* draw(SDL_Renderer *renderer, SDL_Rect cam);
		Pickup(SDL_Rect _rect, char type, int value, Player* player, HUD* h);
        ~Pickup();
		Pickup();
		void checkPickupOverlap(std::unordered_map<std::string, Object*> *objectList);
		SDL_Rect* getRect();
		void updatePosition(Uint32 ticks);
		bool isUsed();
		static int getTotal();
};

#endif  //  BANDCAMP_PICKUP_H_