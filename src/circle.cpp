/* Team Bandcamp
 * Class function: 
 * 
*/

#include "include/circle.h"

int x;
int y;
int r;

// add description
Circle::Circle()
{
    x = 0;
    y = 0;
    r = 0;
}

// add description
Circle::Circle(int varX, int varY, int varR)
{
    x = varX;
    y = varY;
    r = varR;
}

// add description
void Circle::updateCircle(int varX, int varY, int varR)
{
    x = varX;
    y = varY;
    r = varR;
}

// add description
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

// add description
int Circle::getX()
{
    return x;
}

// add description
int Circle::getY()
{
    return y;
}

// add description
int Circle::getR()
{
    return r;
}