#ifndef BANDCAMP_SCREEN_H_
#define BANDCAMP_SCREEN_H_

#include <SDL.h>
#include <vector>
#include "object.h"

class Screen
{
    private:
        bool start;
		std::vector<Object*> roomList;
		SDL_Renderer* rendererReference;
    public:
		virtual void init(SDL_Renderer* renderer) = 0;
		virtual void input(const Uint8* keystate) = 0;
		virtual void update() = 0;
		virtual SDL_Renderer* draw(SDL_Renderer *renderer) = 0;
};

#endif  //  BANDCAMP_SCREEN_H_