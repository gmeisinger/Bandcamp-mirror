#ifndef BANDCAMP_OBJECT_H_
#define BANDCAMP_OBJECT_H_

#include <SDL.h>
#include <vector>
#include <string>

class Object
{		
	public:
		virtual void input(const Uint8* keystate) = 0;
		virtual void init(SDL_Renderer *renderer) = 0;
		virtual void update(std::vector<Object*> *objectList, Uint32 ticks) = 0;
		virtual SDL_Renderer* draw(SDL_Renderer *renderer) = 0;
};

#endif  //  BANDCAMP_OBJECT_H_