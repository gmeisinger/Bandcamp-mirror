#include "include/circle.h"
#include "include/collision.h"

//Collision detection for two rectangles
bool collision::checkCol(SDL_Rect rect1, SDL_Rect rect2) {    
    //Vertical overlap 
    if(rect1.y + rect1.h <= rect2.y)
    {
        return false;
    }
    if(rect1.y >= rect2.y + rect2.h)
    {
        return false;
    }

    //Horizontal overlap
    if(rect1.x + rect1.w <= rect2.x)
    {
        return false;
    }
    if(rect1.x >= rect2.x + rect2.w)
    {
        return false;
    }

    return true;
}

//Collision detection for a rectangle and a circle
bool collision::checkCol(SDL_Rect rect, Circle circ) {
    int closeX = 0;
    int closeY = 0;
    int distX = 0;
    int distY = 0;
    int sq = 0;

    if(circ.getX() < rect.x)
    {
        closeX = rect.x;
    }
    else if (circ.getX() > rect.x + rect.w)
		closeX = rect.x + rect.w;
	else
		closeX = circ.getX();

	if (circ.getY() < rect.y)
		closeY = rect.y;
	else if (circ.getY() > rect.y + rect.h)
		closeY = rect.y + rect.h;
	else
		closeY = circ.getY();

	// Find distance from Circ to Rect
	distX = circ.getX() - closeX;
	distY = circ.getY() - closeY;

	// Compare square of distances
	sq = distX * distX + distY * distY;
	if (sq < (circ.getR() * circ.getR()))
		return true;

	// else
	return false;
}

//Collision detection for two circles
bool collision::checkCol(Circle circ1, Circle circ2) {
    int rad = circ1.getR() + circ2.getR();
	int distX;
    int distY;
	int sq;

	distX = circ1.getX() - circ2.getX();
	distY = circ1.getY() - circ2.getY();
	sq = distX * distX + distY * distY;
	if (sq < (rad * rad))
		return true;
	
	// else
	return false;
}

//Collision detection for a rect and the walls of a tilemap
Tile* collision::checkColTop(SDL_Rect rect, std::vector<std::vector<Tile*>> &grid, int tilesize) {
    //which tiles are we in?
    int normLeftX = rect.x/tilesize;
    int normY = rect.y/tilesize;
    int normRightX = (rect.x + rect.w)/tilesize;
    
    Tile* tileL = grid[normY][normLeftX];
    Tile* tileR = grid[normY][normRightX];
    if(tileL->isBlocking())
		return tileL;
	else if(tileR->isBlocking())
        return tileR;
    else
        return NULL;
}

// add description
Tile* collision::checkColBottom(SDL_Rect rect, std::vector<std::vector<Tile*>> &grid, int tilesize) {
    //which tiles are we in?
    int normLeftX = rect.x/tilesize;
    int normY = (rect.y + rect.h)/tilesize;
    int normRightX = (rect.x + rect.w)/tilesize;
    
    Tile* tileL = grid[normY][normLeftX];
    Tile* tileR = grid[normY][normRightX];
    if(tileL->isBlocking())
		return tileL;
	else if(tileR->isBlocking())
        return tileR;
    else
        return NULL;
}

//Collision detection for a rect and the walls of a tilemap
Tile* collision::checkColLeft(SDL_Rect rect, std::vector<std::vector<Tile*>> &grid, int tilesize) {

    //which tiles are we in?
    int normX = rect.x/tilesize;
    int normTopY = rect.y/tilesize;
    int normBottomY = (rect.y + rect.h)/tilesize;
    
    Tile* tileT = grid[normTopY][normX];
    Tile* tileB = grid[normBottomY][normX];
    if(tileT->isBlocking())
		return tileT;
	else if(tileB->isBlocking())
        return tileB;
    else
        return NULL;
}

// add description
Tile* collision::checkColRight(SDL_Rect rect, std::vector<std::vector<Tile*>> &grid, int tilesize) {
    //which tiles are we in?
    int normX = (rect.x + rect.w)/tilesize;
    int normTopY = rect.y/tilesize;
    int normBottomY = (rect.y + rect.h)/tilesize;
    
    Tile* tileT = grid[normTopY][normX];
    Tile* tileB = grid[normBottomY][normX];
    if(tileT->isBlocking())
		return tileT;
	else if(tileB->isBlocking())
        return tileB;
    else
        return NULL;
}