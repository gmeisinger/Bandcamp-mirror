#include "include/circle.h"

int x;
int y;
int r;

Circle::Circle()
{
    x = 0;
    y = 0;
    r = 0;
}

Circle::Circle(int varX, int varY, int varR)
{
    x = varX;
    y = varY;
    r = varR;
}

void Circle::updateCircle(int varX, int varY, int varR)
{
    x = x;
    y = y;
    r = r;
}

void Circle::drawCircle(SDL_Renderer* rend)
{
    for (int i = -r; i < r; i++) 
    {
		for (int f = -r; f < r; f++) 
        {
			if ((i*i + f*f) < (r*r)) 
            {
                SDL_SetRenderDrawColor(rend, 0, 0xFF, 0, 0);
				SDL_RenderDrawPoint(rend, x + i, y + f);
			}
		}
	}
}

int Circle::getX()
{
    return x;
}

int Circle::getY()
{
    return y;
}

int Circle::getR()
{
    return r;
}