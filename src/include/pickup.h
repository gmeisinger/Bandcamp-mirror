#ifndef BANDCAMP_PICKUP_H_
#define BANDCAMP_PICKUP_H_

#include <vector>
#include <unordered_map>
#include <SDL.h>
#include <string>

#include "player.h"
#include "HUD.h"
#include "object.h"

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
		void input(const Uint8* keystate);
		void init(SDL_Renderer *renderer);
		void update(std::unordered_map<std::string, Object*> *objectList, Uint32 ticks);
		std::string getInstanceName();
		SDL_Renderer* draw(SDL_Renderer *renderer);
		Pickup(SDL_Rect _rect, char type, int value, Player* player, HUD* h);
        ~Pickup();
		Pickup();
		void checkPickupOverlap(std::unordered_map<std::string, Object*> *objectList);
		SDL_Rect* getRect();
		void updatePosition(Uint32 ticks);
		bool isUsed();
};

#endif  //  BANDCAMP_PICKUP_H_