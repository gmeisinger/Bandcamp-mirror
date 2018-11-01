#ifndef BANDCAMP_OBJECT_H_
#define BANDCAMP_OBJECT_H_

#include <SDL.h>
#include <vector>
#include <unordered_map>
#include <string>

class Object
{		
	public:
		virtual std::string getInstanceName() = 0; //A tag to determine instance names.
		virtual void input(const Uint8* keystate) = 0;
		virtual void init(SDL_Renderer *renderer) = 0;
		virtual void update(std::unordered_map<std::string, Object*> *objectList, Uint32 ticks) = 0;
		virtual SDL_Renderer* draw(SDL_Renderer *renderer, SDL_Rect cam) = 0;
		virtual bool isUsed() = 0;
};

#endif  //  BANDCAMP_OBJECT_H_