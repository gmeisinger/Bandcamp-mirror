/* Team Bandcamp
 * Class function: 
 * 
*/

#include <algorithm>
#include <vector>

#include "include/physics.h"
#include "include/pickup.h"
#include "include/player.h"
#include "include/HUD.h"
#include "include/utils.h"
#include "include/testroom.h"

SDL_Rect pickupRect;
char pickupType;
int pickupValue;
bool used = false;

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
	if (checkPickupOverlap(objectList)) delete this;
}

SDL_Renderer* Pickup::draw(SDL_Renderer *renderer){
	SDL_SetRenderDrawColor(renderer, 0x00, 0x30, 0x25, 0xFF);
	SDL_RenderFillRect(renderer, &pickupRect);
	return renderer;
}

//Checks if the player overlapped with the pickup and acts accordingly
bool Pickup::checkPickupOverlap(std::vector<Object*> objectList) {
	if (!used) {
		bool overlap = pickupPlayer->getX() < pickupRect.x + pickupRect.w &&
					   pickupPlayer->getX() + pickupPlayer->getWidth() > pickupRect.x &&
					   pickupPlayer->getY() < pickupRect.y + pickupRect.h &&
					   pickupPlayer->getY() + pickupPlayer->getHeight() > pickupRect.y;

		if (overlap){//(xOverlap && yOverlap) {
			if (pickupType == 'e') {
				hud->currentTemp = std::min(100, hud->currentTemp+pickupValue);
				std::cout << "TEMP UP!" << std::endl;
			} else if (pickupType == 'o') {
				hud->currentOxygen = std::min(100, hud->currentOxygen+pickupValue);
				std::cout << "O2 UP!" << std::endl;
			} else {
				//left just in case we want some other types of pickups later
			}
			used = true;
			return true;
		}
	}
	return false;
}

SDL_Rect* Pickup::getPickupRect() {
    return &pickupRect;
}