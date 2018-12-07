#ifndef BANDCAMP_TESTTRANSITION_1_H_
#define BANDCAMP_TESTTRANSITION_1_H_

#include <SDL.h>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <string>

#include "screen.h"
#include "object.h"
#include "pickup.h"
#include "door.h"
#include "warptile.h"
#include "fadeobj.h"
#include "GSM.h"
#include "tilemap.h"
#include "player.h"
#include "HUD.h"


class TestTransition_1 : public Screen
{
private:
    std::unordered_map<std::string, Object*> objectList;
    SDL_Renderer* rendererReference;
    SDL_Rect fullScreen;
    bool escape; //Have we pushed the escape key ?
    int updateCount;
    HUD h; // Heads up display
    Player p;
    bool fading; //Is the screen fading?
    bool pauseB;
    bool enterHeld; //Have we pushed the pauseButton this frame?
    Tilemap tilemap;
    SDL_Rect camera;
    
public:
    TestTransition_1();
    void init(SDL_Renderer* renderer);
    void input(const Uint8* keystate);
    void update(Uint32 ticks);
    void placeDoors(SDL_Renderer* renderer);
    SDL_Renderer* draw(SDL_Renderer* renderer);
};

#endif  //  BANDCAMP_TESTTRANSITION_1_H_
