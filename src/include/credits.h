#ifndef BANDCAMP_CREDITS_H_
#define BANDCAMP_CREDITS_H_

#include <iostream>
#include <string>
#include <vector>
#include <SDL.h>
#include <SDL_image.h>
#include "utils.h"

class Credits
{
    private:
        bool init;
        std::vector<SDL_Texture*> credits;
        SDL_Renderer* renderer;
    public:
        Credits(SDL_Renderer* _gRenderer);
        ~Credits();
        void load();
        void play();
};
#endif // BANDCAMP_CREDITS_H_