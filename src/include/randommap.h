#ifndef BANDCAMP_RANDOMMAP_H_
#define BANDCAMP_RANDOMMAP_H_

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
#include "global.h"

class RandomMap : public Screen 
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
		Tilemap tilemap;
		SDL_Rect camera;
		SDL_Texture* dark;
	
	public: 
		RandomMap();
		void init(SDL_Renderer* renderer);
		void input(const Uint8* keystate);
		void update(Uint32 ticks);
		void placeDoors(SDL_Renderer* renderer);
		SDL_Renderer* draw(SDL_Renderer* renderer);
		void movePickup(SDL_Renderer* reference, std::vector<std::vector<Tile*>> grid);
		void cloneOoze(SDL_Renderer* reference);
		static void setSpawnPickup(bool set);
		static void setSpawnOoze(bool set);
};

#endif  //  BANDCAMP_TESTROOM_H_
