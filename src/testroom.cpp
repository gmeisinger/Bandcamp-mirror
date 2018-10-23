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
#include "include/gsm.h"
constexpr int UPDATE_MAX = 100;
int updateCount = 1;
int oldTemp = 100;
int oldO2 = 100;

HUD h;
Player p;
Pickup currentP;

TestRoom::TestRoom(){
	start = false;
	std::vector<Object*> objectList;
	//roomReference = &currentScreen;
}

void TestRoom::init(SDL_Renderer* reference){
	std::cout << "Init TestRoom" << std::endl;
	rendererReference = reference;
	SDL_Rect player_box = {screen_w/2, screen_h/2, tile_s, tile_s};
	p = Player(player_box);
	//set up player animations
	p.setSpriteSheet(utils::loadTexture(rendererReference, "res/spaceman.png"), 4, 4);
	p.addAnimation("down", Animation(p.getSheet().getRow(0)));
	p.addAnimation("up", Animation(p.getSheet().getRow(1)));
	p.addAnimation("left", Animation(p.getSheet().getRow(2)));
	p.addAnimation("right", Animation(p.getSheet().getRow(3)));
	p.setAnimation("down");
	
	h.init(reference);
	p.init(reference);
	
	//Player and HUD in the Room
	objectList.push_back(&h);
	objectList.push_back(&p);
}

void TestRoom::update(Uint32 ticks){
	if (h.currentTemp > oldTemp || h.currentOxygen > oldO2) movePickup();
	oldTemp = h.currentTemp;
	oldO2 = h.currentOxygen;
	for(int i=0; i < objectList.size(); i++){
		objectList[i]->update(objectList, ticks);
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

void TestRoom::movePickup() {
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
		
		currentP.used = false;
		
		currentP = Pickup(pickupBox, type, pickupValue, &p, &h);
		objectList.push_back(&currentP);
}

void TestRoom::input(const Uint8* keystate){
	for(int i=0; i < objectList.size(); i++){
		objectList[i]->input(keystate);
	}
}

SDL_Renderer* TestRoom::draw(SDL_Renderer * renderer){
	for(int i=0; i < objectList.size(); i++){	
		renderer = objectList[i]->draw(renderer);
	}
	return renderer;
}