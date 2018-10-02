#include "include/physics.h"
#include "include/pickup.h"
#include "include/player.h"

SDL_Rect pickupRect;
char pickupType;
int pickupValue;
Player *pickupPlayer;

//Constructor - takes a texture, width, height, pickup type, pickup value and player
Pickup::Pickup(SDL_Rect _rect, char type, int value, Player *player) {
    pickupRect = _rect;
	pickupType = type;
	pickupValue = value;
	pickupPlayer = player;
}

//Deconstructor
Pickup::~Pickup() {

}

//Checks if the player overlapped with the pickup and acts accordingly
bool checkPickupOverlap() {
	bool xOverlap = ((pickupPlayer->getX() < pickupRect.x < (pickupPlayer->getX() + pickupPlayer->getWidth())) || 
					 (pickupPlayer->getX() < (pickupRect.x + pickupRect.w) < (pickupPlayer->getX() + pickupPlayer->getWidth())));
	bool yOverlap = ((pickupPlayer->getY() < pickupRect.y < (pickupPlayer->getY() + pickupPlayer->getHeight())) || 
					 (pickupPlayer->getY() < (pickupRect.y + pickupRect.h) < (pickupPlayer->getY() + pickupPlayer->getHeight())));
	if (xOverlap && yOverlap) {
		if (pickupType == 'e') {
			//increase electricity
		} else if (pickupType == 'o') {
			//increase oxygen
		} else {
			//left just in case we want some other types of pickups later
		}
		return true;
	}
	return false;
}

SDL_Rect* Pickup::getPickupRect() {
    return &pickupRect;
}