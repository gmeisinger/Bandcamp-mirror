/* Team Bandcamp
 * Class function: 
 * 
*/

#include <SDL.h>
#include <algorithm>
#include <string>

#include "include/object.h"
#include "include/player.h"
#include "include/spritesheet.h"
#include "include/HUD.h"
#include "include/testroom.h"
#include "include/game.h"

constexpr int UPDATE_MAX = 100;
int updateCount = 1;
int oldTemp = 100;
int oldO2 = 100;

HUD h;
Player p;
bool pauseB, enterHeld; //Have we pushed the pauseButton this frame?

TestRoom::TestRoom() : Screen(){}

void TestRoom::init(SDL_Renderer* reference){
	rendererReference = reference;
	SDL_Rect player_box = {screen_w/2, screen_h/2, tile_s, tile_s};
	p = Player(player_box);
	
	h.init(reference);
	p.init(reference);
	
	//Player and HUD in the Room
	objectList["player"] = &h;
	objectList["hud"] = &p;
}

void TestRoom::update(Uint32 ticks){
	if(pauseB)
	{ //If you set the currentScreen in the Input method it will cause an array out of bounds error.
		pauseB = false;
		enterHeld = true;
		currentScreen = -1;//The Pause Command  <- Its an arbitrary number.
	}
	
	if (h.currentTemp > oldTemp || h.currentOxygen > oldO2) movePickup(rendererReference);
	oldTemp = h.currentTemp;
	oldO2 = h.currentOxygen;
	std::unordered_map<std::string, Object*>::iterator it = objectList.begin();
	while(it != objectList.end()){
		it->second->update(&objectList, ticks);
		if(it->second->isUsed()) {
			it = objectList.erase(it);
		}
		it++;
	}
	if (updateCount == 0) {
		h.currentTemp = std::max(0, h.currentTemp-5);
		h.currentOxygen = std::max(0, h.currentOxygen-5);
		if (h.currentTemp == 0) {
			h.currentHealth = std::max(0, h.currentHealth-5);
		}
		if (h.currentOxygen == 0) {
			h.currentHealth = std::max(0, h.currentHealth-5);
		}
	}
	updateCount = (updateCount+1)%UPDATE_MAX;
}

void TestRoom::movePickup(SDL_Renderer* reference) {
		int pickupX = std::max(tile_s, rand()%(screen_w-tile_s));
		int pickupY = std::max(tile_s, rand()%(screen_h-tile_s));
		SDL_Rect pickupBox = {pickupX, pickupY, tile_s, tile_s};
		
		int pickupValue = rand()%25+25;
		
		int pickupType = rand()%2;
		char type;
		
		if (pickupType == 0)
			type = 'e';
		else
			type = 'o';
		
		Pickup *newP  = new Pickup(pickupBox, type, pickupValue, &p, &h);
		objectList[newP->getInstanceName()] = newP;
		newP->init(reference);
}

void TestRoom::input(const Uint8* keystate){
	//If you push the pause button
	
	//When you come back into the room after a pause, you will most likely still be holding down
	//the enter key. This prevents you from going straight back into the pause menu.
	if(enterHeld && keystate[SDL_SCANCODE_RETURN])
		pauseB = false;
	else
	{
		enterHeld = false;
		pauseB = keystate[SDL_SCANCODE_RETURN];
		
		std::unordered_map<std::string, Object*>::iterator it = objectList.begin();
		while(it != objectList.end()){
			it->second->input(keystate);
			it++;
		}
	}
}

SDL_Renderer* TestRoom::draw(SDL_Renderer *renderer){
	std::unordered_map<std::string, Object*>::iterator it = objectList.begin();
	while(it != objectList.end()){
		renderer = it->second->draw(renderer);
		it++;
	}
	return renderer;
}