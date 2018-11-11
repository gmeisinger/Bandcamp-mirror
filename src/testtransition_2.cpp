/* Team Bandcamp
 * Class function: 
 * 
*/

#include "include/object.h"
#include "include/player.h"
#include "include/spritesheet.h"
#include "include/HUD.h"
#include "include/testtransition_2.h"
#include "include/game.h"
#include "include/GSM.h"
#include "include/circle.h"
#include "include/collision.h"

constexpr int UPDATE_MAX = 100;
constexpr int CAM_WIDTH = 800;
constexpr int CAM_HEIGHT = 600;
WarpTile w_1;
FadeObj f_1;

TestTransition_2::TestTransition_2() : Screen(){
	std::unordered_map<std::string, Object*> objectList;
	updateCount = 1;
	fullScreen = {0,0, SCREEN_WIDTH, SCREEN_HEIGHT};
} //from merge

//TestTransition_2::TestTransition_2(){
//	start = false;
//	std::unordered_map<std::string, Object*> objectList;
//}


// ADD COMMENTS 
void TestTransition_2::init(SDL_Renderer* reference){
	rendererReference = reference;
	SDL_Rect player_box = {SCREEN_WIDTH/2, SCREEN_HEIGHT/2, TILE_SIZE, TILE_SIZE};
	p = Player(player_box);
	map = Tilemap(utils::loadTexture(reference, "res/map_tiles.png"), 30, 20, 32);
	dark = utils::loadTexture(reference, "res/dark.png");
	camera = {p.getX() - CAM_WIDTH/2, p.getY() - CAM_HEIGHT/2, CAM_WIDTH, CAM_HEIGHT};
	w_1 = WarpTile(14, 15, true, true, 1); //WarpTile(int x, int y, bool _insideWall, bool _fade, int _destX, int _destY)
	f_1 = FadeObj(); //Fade the screen in
	
	h.init(reference);
	p.init(reference);
	w_1.init(reference);
	f_1.init(reference);
	map.init();
	map.genMaze();
	
	//Player and HUD in the Room
	objectList["player"] = &p;
	objectList["hud"] = &h;
	objectList[w_1.getInstanceName()] = &w_1;
	objectList["FadeObj"] = &f_1;
	fading = true; //To prevent one frame of light before the fade in.
}

// ADD COMMENTS 
void TestTransition_2::update(Uint32 ticks){
	if(objectList.count("FadeObj")>0){ //only update the fade when you are fading
		fading = true;
		
		objectList["FadeObj"]->update(&objectList, map.getGrid(), ticks);
		
		if(objectList["FadeObj"]->isUsed()){
			fading = false;
			
			if(!static_cast<FadeObj*>(objectList["FadeObj"])->isFadeIn())
				GSM::currentScreen = static_cast<FadeObj*>(objectList["FadeObj"])->getDest(); //If we are fading out go to the next screen. 
			
			delete objectList["FadeObj"]; //If it's malloc'd, delete it.
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
}

// ADD COMMENTS 
void TestTransition_2::input(const Uint8* keystate){
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
SDL_Renderer* TestTransition_2::draw(SDL_Renderer *renderer){
	
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xFF);
	SDL_RenderFillRect(renderer, &fullScreen); //Black Background
	
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	
	//draw map before objects
	map.draw(renderer, camera);
	//draw objects
	std::unordered_map<std::string, Object*>::iterator it = objectList.begin();
	while(it != objectList.end()){
		if(it->first != "FadeObj" && it->first != "hud") //Don't render the fade out here.
			renderer = it->second->draw(renderer, camera);
		it++;
	}
	
    SDL_RenderCopy(renderer, dark, NULL, NULL);

	renderer = objectList["hud"]->draw(renderer, camera);
	
	if(fading)	
		objectList["FadeObj"]->draw(renderer, camera);
	
	return renderer;
}
