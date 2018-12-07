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
#include "include/tilemap.h"
#include "include/box.h"

//constexpr int UPDATE_MAX = 100;
constexpr int CAM_WIDTH = 800;
constexpr int CAM_HEIGHT = 600;

int roomMax = 0;
int doorMax = 0;
int waitTicks = 0;
bool spawnOoze = false;
bool spawnPickup = true;
bool changedHUD = false;
int changedRoomNum = 0;
// Heads up display
HUD h;
Player p;

//Rooms, helps us determine where to spawn ooze and pickups
std::vector<Room*> rooms;
std::vector<Door*> doors;

bool pauseB, enterHeld; //Have we pushed the pauseButton this frame?

Ooze o;
Ooze o2;
Ooze o3;

RandomMap::RandomMap() : Screen(){
    std::unordered_map<std::string, Object*> objectList;
    roomCount = 0;
    doorCount = 0;
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
    objectList.clear();
    rendererReference = reference;
    SDL_Rect player_box = {TILE_SIZE + 1, TILE_SIZE + 1, 30, 30};
    
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
    rooms = tilemap.getRooms();
    doors = {};
    
    placeChests(reference);
    
    //Set the starting room for the ooze
    //std::cout << "numRooms: " << rooms.size() << std::endl;
    Room oozeRoom = *rooms[rand()%(rooms.size())];
    //std::cout << "HERE" << std::endl;
    o = Ooze(&oozeRoom, &tilemap);
    
    o.init(reference);
    //Player and HUD in the Room
    objectList["player"] = &p;
    player = &p;
    objectList["hud"] = &h;
    hud_g = &h;
    // Change to add ooze to list as initialized
    objectList[o.getInstanceName()] = &o;
    
    oozeRoom = *rooms[rand()%(rooms.size())];
    //std::cout << "HERE" << std::endl;
    o2 = Ooze(&oozeRoom, &tilemap);
    
    o2.init(reference);
    // Change to add ooze to list as initialized
    objectList[o2.getInstanceName()] = &o2;
    
    oozeRoom = *rooms[rand()%(rooms.size())];
    //std::cout << "HERE" << std::endl;
    o3 = Ooze(&oozeRoom, &tilemap);
    
    o3.init(reference);
    // Change to add ooze to list as initialized
    objectList[o3.getInstanceName()] = &o3;
    
    //add doors dynamically
    placeDoors(reference);
    
    //objectList[o.getInstanceName()] = &o;
    
}

// ADD COMMENTS
void RandomMap::update(Uint32 ticks){
    //std::cout << std::endl << "Entered RandomMap update" << std::endl;
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
        
        if (waitTicks == 0) {
            if (it->second->getInstanceName().find("breach") != -1) {
                std::vector<Room*> breachRooms = {};
                for(Room* room : rooms) {
                    if(room->contains(it->second->getRect())) {
                        breachRooms.push_back(room);
                    }
                }
                if (breachRooms.size() == 2) {
                    int oxyTarget = (breachRooms[0]->physics.give_oxygen() + breachRooms[1]->physics.give_oxygen()) / 2;
                    int tempTarget = (breachRooms[0]->physics.give_temperature() + breachRooms[1]->physics.give_temperature()) / 2;
                    int presTarget = (breachRooms[0]->physics.give_pressure() + breachRooms[1]->physics.give_pressure()) / 2;
                    breachRooms[0]->physics.changeOxy(oxyTarget);
                    breachRooms[0]->physics.changeTemp(tempTarget);
                    breachRooms[0]->physics.changePres(presTarget);
                    breachRooms[1]->physics.changeOxy(oxyTarget);
                    breachRooms[1]->physics.changeTemp(tempTarget);
                    breachRooms[1]->physics.changePres(presTarget);
                } else if (breachRooms.size() == 1) {
                    int oldPres = breachRooms[0]->physics.give_pressure();
                    breachRooms[0]->physics.changeOxyExternal();
                    breachRooms[0]->physics.changeTempExternal(oldPres);
                }
                breachRooms = {};
            }
        }
        
        if(it->second->isUsed()) {
            if (it->second->getInstanceName().find("Pickup") != -1) {
                for(Room* room : rooms) {
                    if(room->contains(it->second->getRect())) {
                        Pickup* temp = (Pickup*)it->second;
                        if (temp->pickupType == 'o') room->physics.raise_oxygen(temp->pickupValue);
                        else room->physics.raise_temperature(temp->pickupValue);
                    }
                }
            }
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
    
    if (!doors.empty()) {
        doorMax = doors.size();
        Door dr = *(doors[doorCount]);
        if (dr.getState() == 3) {
            int oxyTarget = (dr.rooms[0]->physics.give_oxygen() + dr.rooms[1]->physics.give_oxygen()) / 2;
            int tempTarget = (dr.rooms[0]->physics.give_temperature() + dr.rooms[1]->physics.give_temperature()) / 2;
            dr.rooms[0]->physics.changeOxy(oxyTarget);
            dr.rooms[0]->physics.changeTemp(tempTarget);
            dr.rooms[1]->physics.changeOxy(oxyTarget);
            dr.rooms[1]->physics.changeTemp(tempTarget);
        }
        if (!(doorMax == 0)) doorCount = (doorCount+1)%doorMax;
    }
    
    roomMax = rooms.size();
    Room* ro = tilemap.getRoom(roomCount);
    if (changedHUD && roomCount == changedRoomNum) changedHUD = false;
    SDL_Rect _temp = *(ro->getRect());
    if (!changedHUD && collision::checkCol(*(p.getRect()), {_temp.x*32, _temp.y*32, _temp.w*32, _temp.h*32})) {
        h.currentTemp = ro->physics.give_temperature();
        h.currentOxygen = ro->physics.give_oxygen();
        if (waitTicks == 0) {
            if (h.currentTemp <= 5) h.currentTemp = 0;
            if (h.currentOxygen <= 5) h.currentOxygen = 0;
            if (h.currentTemp == 0) h.currentHealth = std::max(h.currentHealth-1, 0);
            if (h.currentOxygen == 0) h.currentHealth = std::max(h.currentHealth-2, 0);
            if (h.currentTemp == 100 && h.currentOxygen == 100) h.currentHealth = std::min(h.currentHealth+1, 90);
        }
        changedHUD = true;
        changedRoomNum = roomCount;
    }
    roomCount = (roomCount+1)%roomMax;
    waitTicks = (waitTicks+1)%10;
}

// ADD COMMENTS

/*
 // based off of movePickup
 void RandomMap::cloneOoze(SDL_Renderer* reference) {
	
 <<<<<<< HEAD
	/*if(collision::checkCol(OozeBox, leftWall)
 || collision::checkCol(OozeBox, rightWall)
 || collision::checkCol(OozeBox, upperWall)
 || collision::checkCol(OozeBox, centerPillar))
	{
 moveOoze(reference);
	}
 =======
 >>>>>>> master
	Room oozeRoom = *rooms[rand()%(rooms.size())];
	Ooze *newO = new Ooze(&oozeRoom, &tilemap);
	objectList[newO->getInstanceName()] = newO;
	newO->init(reference);
	spawnOoze = false; //don't need a new pickup; one was just made
 }*/

// based off of movePickup
void RandomMap::cloneOoze(SDL_Renderer* reference) {
    /*
     std::unordered_map<std::string, Object*>::iterator it = objectList.begin();
     while(it != objectList.end()){
     if (it->second->getInstanceName().find("Ooze") != -1) {
     Ooze *newO = new Ooze(*static_cast<Ooze*>(it->second));
     objectList[newO->getInstanceName()] = newO;
     //            newO->init(reference);
     break;
     }
     it++;
     }*/
    std::cout << "randommap trying to clone" << std::endl;
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
    if(enterHeld && (keystate[SDL_SCANCODE_RETURN] || keystate[SDL_SCANCODE_ESCAPE]))
        pauseB = false;
    else
    {
        enterHeld = false;
        pauseB = keystate[SDL_SCANCODE_RETURN] || keystate[SDL_SCANCODE_ESCAPE];
        
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
                for(Room* room : rooms) {
                    if(room->contains(d->getRect())) {
                        d->addRoom(room);
                        doors.push_back(d);
                    }
                }
            }
        }
    }
}

void RandomMap::placeChests(SDL_Renderer* renderer) {
    std::vector<std::vector<Tile*>> &map = tilemap.getMapRef();
    for(int r=0;r<map.size();r++) {
        for(int c=0;c<map[0].size();c++) {
            if(map[r][c]->isChest()) { 
                Box* b = new Box(c, r);
                b->init(renderer);
                objectList[b->getInstanceName()] = b;
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
