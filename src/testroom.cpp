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
#include "include/ooze.h"
#include "include/circle.h"
#include "include/collision.h"

constexpr int UPDATE_MAX = 100;
constexpr int CAM_WIDTH = 800;
constexpr int CAM_HEIGHT = 600;
int updateCount = 1;
int oldTemp = 100;
int oldO2 = 100;

HUD h;
Player p;
Ooze o;
SDL_Rect leftWall;
SDL_Rect rightWall;
SDL_Rect upperWall;
Circle centerPillar;
Tilemap map;
SDL_Rect camera;

TestRoom::TestRoom(int* roomNumber){
	start = false;
	std::unordered_map<std::string, Object*> objectList;
	roomReference = roomNumber;
}

void TestRoom::init(SDL_Renderer* reference){
	rendererReference = reference;
	SDL_Rect player_box = {screen_w/2, screen_h/2, tile_s, tile_s};
	p = Player(player_box);
	SDL_Rect ooze_box = {screen_w/2, 3*screen_h/8, 30, 30};
	o = Ooze(ooze_box, &p, &h);
	map = Tilemap(utils::loadTexture(reference, "res/map_tiles.png"), 50, 36, 32);
	camera = {p.getX() - CAM_WIDTH/2, p.getY() - CAM_HEIGHT/2, CAM_WIDTH, CAM_HEIGHT};
    
	h.init(reference);
	p.init(reference);
	o.init(reference);
	map.init();
	map.genTestRoom();
	
	//Player and HUD in the Room
	objectList["player"] = &p;
	objectList["hud"] = &h;
	objectList["ooze"] = &o;

	//Init walls in the room
	//leftWall = {screen_w/4, screen_h/4, screen_w/12, screen_h/2};
	//rightWall = {screen_w/4 * 3 - screen_w/12, screen_h/4, screen_w/12, screen_h/2};
	//upperWall = {screen_w/4, screen_h/4, screen_w/2, screen_h/12};
	//centerPillar = {screen_w/2, screen_h/2 + (tile_s * 5), tile_s};
}

void TestRoom::update(Uint32 ticks){
	if (h.currentTemp > oldTemp || h.currentOxygen > oldO2) movePickup(rendererReference);
	oldTemp = h.currentTemp;
	oldO2 = h.currentOxygen;
	//update all objects
	std::unordered_map<std::string, Object*>::iterator it = objectList.begin();
	while(it != objectList.end()){
		it->second->update(&objectList, ticks);
		if(it->second->isUsed()) {
			it = objectList.erase(it);
		}
		it++;
	}
	//update camera to player position
	camera.x = p.getX() - (camera.w/2);
	camera.y = p.getY() - (camera.h/2);

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
	
	if(collision::checkCol(pickupBox, leftWall) 
		|| collision::checkCol(pickupBox, rightWall)
		|| collision::checkCol(pickupBox, upperWall)
		|| collision::checkCol(pickupBox, centerPillar))
	{
		movePickup(reference);
	}
	else
	{
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
}

void TestRoom::input(const Uint8* keystate){
	std::unordered_map<std::string, Object*>::iterator it = objectList.begin();
	while(it != objectList.end()){
		it->second->input(keystate);
		it++;
	}
}

SDL_Renderer* TestRoom::draw(SDL_Renderer *renderer){
	//draw map before objects
	map.draw(renderer, camera);
	//draw objects
	std::unordered_map<std::string, Object*>::iterator it = objectList.begin();
	while(it != objectList.end()){
		renderer = it->second->draw(renderer, camera);
		it++;
	}

	//Draws walls in the room
	//SDL_SetRenderDrawColor(renderer, 0, 0xFF, 0, 0);
	//SDL_RenderFillRect(renderer, &leftWall);
	//SDL_RenderFillRect(renderer, &rightWall);
	//SDL_RenderFillRect(renderer, &upperWall);
	//centerPillar.drawCircle(renderer);

	return renderer;
}
