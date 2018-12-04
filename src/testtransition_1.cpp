/* Team Bandcamp
 * Class function: 
 * 
*/

#include "include/object.h"
#include "include/player.h"
#include "include/spritesheet.h"
#include "include/HUD.h"
#include "include/testtransition_1.h"
#include "include/game.h"
#include "include/GSM.h"
#include "include/circle.h"
#include "include/collision.h"

constexpr int UPDATE_MAX = 100;
constexpr int CAM_WIDTH = 800;
constexpr int CAM_HEIGHT = 600;
//Door d_1;
WarpTile w;
FadeObj f;

TestTransition_1::TestTransition_1() : Screen(){
	std::unordered_map<std::string, Object*> objectList;
	updateCount = 1;
	fullScreen = {0,0, SCREEN_WIDTH, SCREEN_HEIGHT};
} //from merge

//TestTransition_1::TestTransition_1(){
//	start = false;
//	std::unordered_map<std::string, Object*> objectList;
//}


// ADD COMMENTS 
void TestTransition_1::init(SDL_Renderer* reference){
	rendererReference = reference;
	SDL_Rect player_box = {SCREEN_WIDTH/2, SCREEN_HEIGHT/2, TILE_SIZE, TILE_SIZE};
	p = Player(player_box);
	tilemap = Tilemap(utils::loadTexture(reference, "res/map_tiles.png"), 30, 20, 32);
	camera = {p.getX() - CAM_WIDTH/2, p.getY() - CAM_HEIGHT/2, CAM_WIDTH, CAM_HEIGHT};
	//d_1 = Door(14,5,true);
	w = WarpTile(14, 4, true, true, 2); //WarpTile(int x, int y, bool _insideWall, bool _fade, int _destScreen)
	f = FadeObj(); //Fade the screen in
	
	h.init(reference);
	p.init(reference);
	//d_1.init(reference);
	w.init(reference);
	f.init(reference);
	tilemap.init();
	tilemap.genTestTransitionRoom();
	placeDoors(reference);
	
	//Player and HUD in the Room
	//objectList["door"] = &d_1;
	objectList["player"] = &p;
	objectList["hud"] = &h;
	objectList[w.getInstanceName()] = &w;
	objectList["FadeObj"] = &f;
	fading = true; //To prevent one frame of light before the fade in.
}

void TestTransition_1::placeDoors(SDL_Renderer* renderer) {
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
				map[r][c]->setBlocking(true);
				Door* d = new Door(c, r, horz);
				d->init(renderer);
				objectList["door"+doorCount] = d;
				doorCount++;
			}
		}
	}
}

// ADD COMMENTS 
void TestTransition_1::update(Uint32 ticks){
	std::cout << std::endl << "Entered TestTransition_1 update" << std::endl;
	std::unordered_map<std::string, Object*>& objectListRef = objectList;
	if(objectList.count("FadeObj")>0){ //only update the fade when you are fading
		fading = true;
		
		objectList["FadeObj"]->update(objectListRef, tilemap.getMapRef(), ticks);
		
		if(objectList["FadeObj"]->isUsed()){
			fading = false;
			
			if(!static_cast<FadeObj*>(objectList["FadeObj"])->isFadeIn())
				GSM::currentScreen = static_cast<FadeObj*>(objectList["FadeObj"])->getDest(); //If we are fading out go to the next screen. 
			
			objectList.erase("FadeObj");
		}
	}
	else{
		fading = false;
		
		if(pauseB)
		{ //If you set the currentScreen in the Input method it will cause an array out of bounds error.
			pauseB = false;
			enterHeld = true;
			GSM::currentScreen = -1;//The Pause Command  <- Its an arbitrary number.
		}

		//update all objects
		std::unordered_map<std::string, Object*>::iterator it = objectList.begin();
		while(it != objectList.end()){
			it->second->update(objectListRef, tilemap.getMapRef(), ticks);
			if(it->second->isUsed()) {
				std::cout << "About to remove object from list (TestTransition_1)" << std::endl;
				it = objectList.erase(it);
				std::cout << "Succeeded in removing object from list (TestTransition_1)" << std::endl;
				break;
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
	std::cout << "Exited TestTransition_1 update" << std::endl << std::endl;
}

// ADD COMMENTS 
void TestTransition_1::input(const Uint8* keystate){
	//If you push the pause button
	
	if(!fading) //Don't take any new input while fading.
	{
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
}

// ADD COMMENTS 
SDL_Renderer* TestTransition_1::draw(SDL_Renderer *renderer){
	
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xFF);
	SDL_RenderFillRect(renderer, &fullScreen); //Black Background
	
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	
	//draw map before objects
	tilemap.draw(renderer, camera);
	//draw objects
	std::unordered_map<std::string, Object*>::iterator it = objectList.begin();
	while(it != objectList.end()){
		if(it->first != "FadeObj") //Don't render the fade out here.
			renderer = it->second->draw(renderer, camera);
		it++;
	}

	if(fading)
		objectList["FadeObj"]->draw(renderer, camera);
	
	return renderer;
}
