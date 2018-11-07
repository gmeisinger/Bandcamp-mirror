/* Team Bandcamp
 * Class function: 
 * 
*/

#include "include/object.h"
#include "include/player.h"
#include "include/spritesheet.h"
#include "include/HUD.h"
#include "include/testroom.h"
#include "include/game.h"
#include "include/GSM.h"
#include "include/ooze.h"
#include "include/circle.h"
#include "include/collision.h"
#include "include/door.h"

constexpr int UPDATE_MAX = 100;
constexpr int CAM_WIDTH = 800;
constexpr int CAM_HEIGHT = 600;
int updateCount = 1;
int oldTemp = 100;
int oldO2 = 100;
int oldAte = 0;

// Heads up display 
HUD h;
Player p;

bool pauseB, enterHeld; //Have we pushed the pauseButton this frame?

TestRoom::TestRoom() : Screen(){
	std::unordered_map<std::string, Object*> objectList;
} //from merge

Ooze o;
Tilemap map;
SDL_Rect camera;
Door d;

//TestRoom::TestRoom(){
//	start = false;
//	std::unordered_map<std::string, Object*> objectList;
//}


// ADD COMMENTS 
void TestRoom::init(SDL_Renderer* reference){
	rendererReference = reference;
	SDL_Rect player_box = {SCREEN_WIDTH/4, 2*TILE_SIZE, TILE_SIZE, TILE_SIZE};
	p = Player(player_box);
	SDL_Rect ooze_box = {SCREEN_WIDTH/2, 3*SCREEN_HEIGHT/8, 30, 30};
	o = Ooze(ooze_box, &p, &h);
	map = Tilemap(utils::loadTexture(reference, "res/map_tiles.png"), 21, 20, 32);
	camera = {p.getX() - CAM_WIDTH/2, p.getY() - CAM_HEIGHT/2, CAM_WIDTH, CAM_HEIGHT};
	d = Door(4,4);
	
	
	h.init(reference);
	p.init(reference);
	o.init(reference);
	d.init(reference);
	map.init();
	map.genTestRoom();
	
	//Player and HUD in the Room
	objectList["player"] = &p;
	objectList["hud"] = &h;
	// Change to add ooze to list as initialized
	//objectList["ooze"] = &o;
	objectList["door"] = &d;
}

// ADD COMMENTS 
void TestRoom::update(Uint32 ticks){
	if(pauseB)
	{ //If you set the currentScreen in the Input method it will cause an array out of bounds error.
		pauseB = false;
		enterHeld = true;
		GSM::currentScreen = -1;//The Pause Command  <- Its an arbitrary number.
	}
	
	// TODO: better way to check for pickup being consumed?
	if (h.currentTemp > oldTemp || h.currentOxygen > oldO2 || o.getAte() > oldAte) movePickup(rendererReference);
	oldTemp = h.currentTemp;
	oldO2 = h.currentOxygen;
	oldAte = o.getAte();
  //update all objects
	std::unordered_map<std::string, Object*>::iterator it = objectList.begin();
	while(it != objectList.end()){
		it->second->update(&objectList, map.getGrid(), ticks);
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

// ADD COMMENTS 
void TestRoom::movePickup(SDL_Renderer* reference) {
	int pickupX = std::max(TILE_SIZE, rand()%(SCREEN_WIDTH-TILE_SIZE));
	int pickupY = std::max(TILE_SIZE, rand()%(SCREEN_HEIGHT-TILE_SIZE));
	SDL_Rect pickupBox = {pickupX, pickupY, TILE_SIZE, TILE_SIZE};
	
	/*if(collision::checkCol(pickupBox, leftWall) 
		|| collision::checkCol(pickupBox, rightWall)
		|| collision::checkCol(pickupBox, upperWall)
		|| collision::checkCol(pickupBox, centerPillar))
	{
		movePickup(reference);
	}*/
	if(false){}
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

// ADD COMMENTS 
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

// ADD COMMENTS 
SDL_Renderer* TestRoom::draw(SDL_Renderer *renderer){
	//draw map before objects
	map.draw(renderer, camera);
	//draw objects
	std::unordered_map<std::string, Object*>::iterator it = objectList.begin();
	while(it != objectList.end()){
		renderer = it->second->draw(renderer, camera);
		it++;
	}

	return renderer;
}
