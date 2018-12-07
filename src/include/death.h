#ifndef BANDCAMP_DEATH_H_
#define BANDCAMP_DEATH_H_

#include <SDL.h>
#include <vector>
#include "screen.h"
#include "animation.h"
#include "spritesheet.h"
#include "utils.h"
//#include "GSM.h"

class Death : public Screen
{
private:
    SpriteSheet ss;
    Animation anim;
    SDL_Rect fRect;
    int alpha;
    int elapsed;
public:
    Death();
    void init(SDL_Renderer* renderer);
    void input(const Uint8* keystate);
    void update(Uint32 ticks);
    SDL_Renderer* draw(SDL_Renderer* renderer);
};

#endif  //  BANDCAMP_DEATH_H_
