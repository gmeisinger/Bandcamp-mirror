/* Team Bandcamp
 * Class function: 
 * 
*/

#include "include/object.h"
#include "include/player.h"
#include "include/spritesheet.h"
#include "include/HUD.h"
#include "include/randommap.h"
#include "include/ooze.h" //Putting these include in testroom.h aparently causes a circular include.
#include "include/game.h"
#include "include/GSM.h"
#include "include/circle.h"
#include "include/collision.h"
#include "include/pickup.h"

constexpr int UPDATE_MAX = 100;
constexpr int CAM_WIDTH = 800;
constexpr int CAM_HEIGHT = 600;

Ooze o;
Door d;
static bool spawnPickup = true;
RandomMap::RandomMap() : Screen(){
	std::unordered_map<std::string, Object*> objectList;
	updateCount = 1;
	oldTemp = 100;
	oldO2 = 100;
	oldAte = 0;
} //from merge

//RandomMap::RandomMap(){
//	start = false;
//	std::unordered_map<std::string, Object*> objectList;
//}

// ADD COMMENTS 
void RandomMap::init(SDL_Renderer* reference){
	rendererReference = reference;
	SDL_Rect player_box = {tile_s + 1, tile_s + 1, tile_s, tile_s};

	p = Player(player_box);
	SDL_Rect ooze_box = {SCREEN_WIDTH/2, 3*SCREEN_HEIGHT/8, 30, 30};
	o = Ooze(ooze_box, &p, &h);
	tilemap = Tilemap(utils::loadTexture(reference, "res/map_tiles.png"), 40, 40, 32);
	camera = {p.getX() - CAM_WIDTH/2, p.getY() - CAM_HEIGHT/2, CAM_WIDTH, CAM_HEIGHT};
	d = Door(4,4);
	
	
	h.init(reference);
	p.init(reference);
	o.init(reference);
	tilemap.init();
	tilemap.setMap(tilemap.genRandomMap());
	d.init(reference);

	
	//Player and HUD in the Room
	objectList["player"] = &p;
	objectList["hud"] = &h;
	// Change to add ooze to list as initialized
	//objectList["ooze"] = &o;
	objectList["door"] = &d;
}

// ADD COMMENTS 
void RandomMap::update(Uint32 ticks){
	if(pauseB)
	{ //If you set the currentScreen in the Input method it will cause an array out of bounds error.
		pauseB = false;
		enterHeld = true;
		GSM::currentScreen = -1;//The Pause Command  <- Its an arbitrary number.
	}

	std::vector<std::vector<int>> grid = tilemap.getMap();

	if (spawnPickup) movePickup(rendererReference); //new way of deciding when to spawn pickup
	// TODO: better way to check for pickup being consumed?
	/*if (h.currentTemp > oldTemp || h.currentOxygen > oldO2 || o.getAte() > oldAte) movePickup(rendererReference);
	oldTemp = h.currentTemp;
	oldO2 = h.currentOxygen;

	oldAte = o.getAte();
	oldAte = o.getAte();*/


	std::unordered_map<std::string, Object*>::iterator it = objectList.begin();
	while(it != objectList.end()){
		it->second->update(&objectList, grid, ticks);
		if(it->second->isUsed()) {
			it = objectList.erase(it);
		}
		it++;
	}
	//update camera to player position
	camera.x = p.getX() - (camera.w/2);
	camera.y = p.getY() - (camera.h/2);
	//the following code will lock the camera to the corners
	//doesnt look right when the map is too small
	/*if(camera.x < 0) {
		camera.x = 0;
	}
	if(camera.y < 0) {
		camera.y = 0;
	}
	if(camera.x > (grid[0].size() * tile_s)) {
		camera.x = grid[0].size() * tile_s;
	}
	if(camera.y > (grid.size() * tile_s)) {
		camera.y = grid.size() * tile_s;
	}*/

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

void RandomMap::movePickup(SDL_Renderer* reference) {
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
		spawnPickup = false; //don't need a new pickup; one was just made
	}
}

// used to allow other objects to tell testroom to spawn a pickup
void RandomMap::setSpawnPickup(bool set) {
	spawnPickup = set;
}
// ADD COMMENTS 
void RandomMap::input(const Uint8* keystate){
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
SDL_Renderer* RandomMap::draw(SDL_Renderer *renderer){
	//draw map before objects
	tilemap.draw(renderer, camera);
	//draw objects
	std::unordered_map<std::string, Object*>::iterator it = objectList.begin();
	while(it != objectList.end()){
		renderer = it->second->draw(renderer, camera);
		it++;
	}

	return renderer;
}
