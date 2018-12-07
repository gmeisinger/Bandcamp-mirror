#ifndef BANDCAMP_SCREEN_H_
#define BANDCAMP_SCREEN_H_

#include <SDL.h>
#include <vector>
#include "object.h"

extern int currentScreen;

class Screen
{
private:
    std::vector<Object*> roomList;
    SDL_Renderer* rendererReference;
    
public:
    bool start;
    SDL_Rect camera;
    virtual void init(SDL_Renderer* renderer) = 0;
    virtual void input(const Uint8* keystate) = 0;
    virtual void update(Uint32 ticks) = 0;
    virtual SDL_Renderer* draw(SDL_Renderer * renderer) = 0;
    //EXIT METHOD??
};

#endif  //  BANDCAMP_SCREEN_H_
