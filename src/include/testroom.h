#ifndef BANDCAMP_TESTROOM_H_
#define BANDCAMP_TESTROOM_H_

#include <SDL.h>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <string>

#include "screen.h"
#include "object.h"
#include "ooze.h"
#include "pickup.h"
#include "door.h"
#include "GSM.h"
#include "tilemap.h"

class TestRoom : public Screen 
{ 
	private:
		std::unordered_map<std::string, Object*> objectList;
		SDL_Renderer* rendererReference;
		bool escape; //Have we pushed the escape key ?
		int updateCount;
		int oldTemp;
		int oldO2;
		int oldAte;
		HUD h; 	// Heads up display 
		Player p;
		bool pauseB; //Have we pushed the pauseButton this frame?
		bool enterHeld; 
		Tilemap map;
		SDL_Rect camera;
	
	public: 
		//static bool spawnPickup;
		TestRoom();
		void init(SDL_Renderer* renderer);
		void input(const Uint8* keystate);
		void update(Uint32 ticks);
		SDL_Renderer* draw(SDL_Renderer* renderer);
		void movePickup(SDL_Renderer* reference);
		static void setSpawnPickup(bool set);
};

#endif  //  BANDCAMP_TESTROOM_H_