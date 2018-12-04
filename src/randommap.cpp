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

bool spawnOoze = false;
// Heads up display 
HUD h;
Player p;

//Rooms, helps us determine where to spawn ooze and pickups
std::vector<Room*> rooms;

bool pauseB, enterHeld; //Have we pushed the pauseButton this frame?

Ooze o;
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
	SDL_Rect player_box = {TILE_SIZE + 1, TILE_SIZE + 1, TILE_SIZE, TILE_SIZE};

	p = Player(player_box);
	//
	//SDL_Rect ooze_box = {SCREEN_WIDTH/2, 3*SCREEN_HEIGHT/8, 30, 30};
	//o = Ooze(ooze_box, &p, &h);
	//
	tilemap = Tilemap(utils::loadTexture(reference, "res/map_tiles.png"), 40, 40, 32);
	camera = {p.getX() - CAM_WIDTH/2, p.getY() - CAM_HEIGHT/2, CAM_WIDTH, CAM_HEIGHT};
	dark = utils::loadTexture(reference, "res/dark.png");
	
	h.init(reference);
	p.init(reference);
	
	tilemap.init();
	tilemap.genRandomMap();
	//Set the starting room for the ooze
	rooms = tilemap.getRooms();
	std::cout << "numRooms: " << rooms.size() << std::endl;
	Room oozeRoom = *rooms[rand()%(rooms.size())];
	o = Ooze(&oozeRoom);


	o.init(reference);
	//Player and HUD in the Room
	objectList["player"] = &p;
    player = &p;
	objectList["hud"] = &h;
    hud_g = &h;
	// Change to add ooze to list as initialized
	//objectList["ooze"] = &o;

	//add doors dynamically
	placeDoors(reference);
	objectList[o.getInstanceName()] = &o;
}

// ADD COMMENTS 
void RandomMap::update(Uint32 ticks){
	if(pauseB)
	{ //If you set the currentScreen in the Input method it will cause an array out of bounds error.
		pauseB = false;
		enterHeld = true;
		GSM::currentScreen = -1;//The Pause Command  <- Its an arbitrary number.
	}
	std::vector<std::vector<Tile*>> &grid = tilemap.getMapRef();

	if (spawnPickup) movePickup(rendererReference, grid); //new way of deciding when to spawn pickup
	if (spawnOoze) cloneOoze(rendererReference);

	std::unordered_map<std::string, Object*>& objectListRef = objectList;
	std::unordered_map<std::string, Object*>::iterator it = objectList.begin();
	while(it != objectList.end()){
		it->second->update(objectListRef, tilemap.getMapRef(), ticks);
		if(it->second->isUsed()) {
			it = objectList.erase(it);
			break;
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

// based off of movePickup
// TODO: finish this shit
void RandomMap::cloneOoze(SDL_Renderer* reference) {
	//int OozeX = std::max(tile_s, rand()%(screen_w-tile_s));
	//int OozeY = std::max(tile_s, rand()%(screen_h-tile_s));
	//SDL_Rect OozeBox = {OozeX, OozeY, tile_s, tile_s};

	
	/*if(collision::checkCol(OozeBox, leftWall) 
		|| collision::checkCol(OozeBox, rightWall)
		|| collision::checkCol(OozeBox, upperWall)
		|| collision::checkCol(OozeBox, centerPillar))
	{
		moveOoze(reference);
	}*/
	Room oozeRoom = *rooms[rand()%(rooms.size())];
	Ooze *newO = new Ooze(&oozeRoom);
	objectList[newO->getInstanceName()] = newO;
	newO->init(reference);
	spawnOoze = false; //don't need a new pickup; one was just made
}

// ADD COMMENTS 
void RandomMap::movePickup(SDL_Renderer* reference, std::vector<std::vector<Tile*>> &grid) {
	Room tempRoom = *rooms.at(rand()%(rooms.size()));
	SDL_Rect *temp = tempRoom.getRect();
	SDL_Rect pickupBox = {(temp->x + rand()%(temp->w)) * tile_s, (temp->y + rand()%(temp->h)) * tile_s, tile_s, tile_s};
	
	if(collision::checkColLeft(pickupBox, grid, 32) 
	|| collision::checkColRight(pickupBox, grid, 32)
	|| collision::checkColTop(pickupBox, grid, 32) 
	|| collision::checkColBottom(pickupBox, grid, 32)) {
		movePickup(reference, grid);
		return;
	}

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

void RandomMap::setSpawnOoze(bool set) {
	spawnOoze = set;
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

void RandomMap::placeDoors(SDL_Renderer* renderer) {
	int doorCount = 0;
	std::vector<std::vector<Tile*>> &map = tilemap.getMapRef();
	for(int r=0;r<map.size();r++) {
		for(int c=0;c<map[0].size();c++) {
			if(map[r][c]->isDoor()) { //horizontal door
				//check for horizontal/vertical
				bool horz = true;
				if(r > 0 && r < map.size()-1 && c > 0 && c < map[0].size()-1) {
					if(map[r+1][c]->isBlocking() || map[r-1][c]->isBlocking()) {
						horz = false;
					}
				}
				//map[r][c]->setBlocking(true);
				Door* d = new Door(c, r, horz);
				d->init(renderer);
				objectList["door"+doorCount] = d;
				doorCount++;
			}
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

	//draw the darkness
	SDL_Rect enlarge = {-CAM_WIDTH/2 - TILE_SIZE, -CAM_HEIGHT/2 - TILE_SIZE, 2*CAM_WIDTH, 2*CAM_HEIGHT};
	SDL_RenderCopy(renderer, dark, NULL, &enlarge);

	//draw the HUD
	auto hud = objectList.find("hud");
	hud->second->draw(renderer, camera);

	return renderer;
}
