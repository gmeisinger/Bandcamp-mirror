#ifndef BANDCAMP_PICKUP_H_
#define BANDCAMP_PICKUP_H_

#include <vector>
#include <SDL.h>
#include <string>

#include "player.h"
#include "HUD.h"
#include "object.h"

class Pickup : public Object
{
	private:
		SDL_Rect pickupRect;
		char pickupType;
		int pickupValue;
		Player *pickupPlayer;
		HUD *hud;

	public:
		void input(const Uint8* keystate);
		void init(SDL_Renderer *renderer);
		void update(std::vector<Object*> objectList);
		SDL_Renderer* draw(SDL_Renderer *renderer);
		Pickup(SDL_Rect _rect, char type, int value, Player* player, HUD* h);
        ~Pickup();
		Pickup();
		bool checkPickupOverlap(std::vector<Object*> objectList);
		SDL_Rect* getPickupRect();
};

#endif  //  BANDCAMP_PICKUP_H_