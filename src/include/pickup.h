#ifndef BANDCAMP_PICKUP_H_
#define BANDCAMP_PICKUP_H_

#include "player.h"

class Pickup
{
	private:
		SDL_Rect pickupRect;
		char pickupType;
		int pickupValue;
		Player *pickupPlayer;

	public:
		Pickup(SDL_Rect _rect, char type, int value, Player *player);
        ~Pickup();
		bool checkPickupOverlap();
		SDL_Rect* getPickupRect();
};

#endif  //  BANDCAMP_PICKUP_H_