#ifndef BANDCAMP_COLLISION_H_
#define BANDCAMP_COLLISION_H_

#include <iostream>
#include <string>
#include <vector>
#include <SDL.h>
#include <SDL_image.h>
#include "circle.h"

namespace collision
{
    bool checkCol(SDL_Rect rect1, SDL_Rect rect2);
    bool checkCol(SDL_Rect rect, Circle circ);
    bool checkCol(Circle circ1, Circle circ2);
    bool checkColX(SDL_Rect rect, std::vector<std::vector<int>> &grid, int tilesize);
    bool checkColY(SDL_Rect rect, std::vector<std::vector<int>> &grid, int tilesize);
};
#endif