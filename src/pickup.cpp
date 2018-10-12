#include <vector>

#include "include/physics.h"
#include "include/pickup.h"
#include "include/player.h"
#include "include/HUD.h"

SDL_Rect pickupRect;
char pickupType;
int pickupValue;

//Constructor - takes a texture, width, height, pickup type, pickup value and player
Pickup::Pickup(SDL_Rect _rect, char type, int value, Player *player, HUD *h) {
    pickupRect = _rect;
	pickupType = type;
	pickupValue = value;
	pickupPlayer = player;
	hud = h;
}

//Deconstructor
Pickup::~Pickup() {

}

Pickup::Pickup(){
	
}

void Pickup::input(const Uint8* keystate){
	
}

void Pickup::init(SDL_Renderer *renderer){
	
}
		
void Pickup::update(std::vector<Object*> objectList, Uint32 ticks){
	checkPickupOverlap(objectList);
}

SDL_Renderer* Pickup::draw(SDL_Renderer *renderer){
	SDL_SetRenderDrawColor(renderer, 0x00, 0x30, 0x25, 0xFF);
	SDL_RenderFillRect(renderer, &pickupRect);
	return renderer;
}


//Checks if the player overlapped with the pickup and acts accordingly
bool Pickup::checkPickupOverlap(std::vector<Object*> objectList) {

	bool overlap = pickupPlayer->getX() < pickupRect.x + pickupRect.w &&
	pickupPlayer->getX() + pickupPlayer->getWidth() > pickupRect.x &&
	pickupPlayer->getY() < pickupRect.y + pickupRect.h &&
	pickupPlayer->getY() + pickupPlayer->getHeight() > pickupRect.y;

	if (overlap){//(xOverlap && yOverlap) {
		if (pickupType == 'e') {
			hud->currentTemp+= 20;
			std::cout << "TEMP UP!" << std::endl;
		} else if (pickupType == 'o') {
			hud->currentOxygen+= 20;
			std::cout << "O2 UP!" << std::endl;
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