#ifndef BANDCAMP_TESTROOM_H_
#define BANDCAMP_TESTROOM_H_

#include <SDL.h>
#include <vector>
#include <unordered_map>

#include "screen.h"
#include "object.h"
#include "pickup.h"
#include "gsm.h"
class TestRoom : public Screen 
{ 
	private:
		bool start;
		std::unordered_map<std::string, Object*> objectList;
		int* roomReference;
		SDL_Renderer* rendererReference;
		bool escape; //Have we pushed the escape key ?
		int updateCount;
		int oldTemp;
		int oldO2;
	
	public: 
		TestRoom();
		void init(SDL_Renderer* renderer);
		void input(const Uint8* keystate);
		void update(Uint32 ticks);
		SDL_Renderer* draw(SDL_Renderer* renderer);
		void movePickup(SDL_Renderer* reference);
};

#endif  //  BANDCAMP_TESTROOM_H_