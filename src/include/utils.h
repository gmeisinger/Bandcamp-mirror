#ifndef BANDCAMP_UTILS_H_
#define BANDCAMP_UTILS_H_

#include <string>
#include <iostream>
#include <vector>
#include <SDL.h>
#include <SDL_image.h>
#include <random>
#include <chrono>

namespace utils
{
    SDL_Texture* loadTexture(SDL_Renderer* renderer, std::string fname);
    void destroyTextureVector(std::vector<SDL_Texture*> vect);
    int normDist();
    int uniformDist();
};
#endif  //  BANDCAMP_UTILS_H_
