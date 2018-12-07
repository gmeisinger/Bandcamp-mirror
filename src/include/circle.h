#ifndef BANDCAMP_CIRCLE_H_
#define BANDCAMP_CIRCLE_H_

#include <iostream>
#include <string>
#include <vector>
#include <SDL.h>
#include <SDL_image.h>
#include "utils.h"

class Circle
{
private:
    int x;
    int y;
    int r;
public:
    Circle();
    Circle(int varX, int varY, int varR);
    void updateCircle(int varX, int varY, int varR);
    void drawCircle(SDL_Renderer* rend);
    int getX();
    int getY();
    int getR();
};
#endif
