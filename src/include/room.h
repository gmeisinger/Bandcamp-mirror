#ifndef BANDCAMP_ROOM_H_
#define BANDCAMP_ROOM_H_

#include <SDL.h>
#include <vector>

#include "physics.h"
#include "utils.h"

class Room
{
private:
	SDL_Rect rect;
	std::vector<Room*> neighbors;
	std::vector<SDL_Rect> intersect_rects;
	Room2 physics;
public:
	Room();
	Room(SDL_Rect _rect);
	~Room();
	SDL_Rect* getRect();
	SDL_Rect getRectCopy();
	SDL_Rect* move(int _x, int _y);
	void addNeighbor(Room* room);
	void addIntersect(SDL_Rect rect);
	std::vector<Room*> getNeighbors();
	std::vector<SDL_Rect> getIntersects();
};

#endif  //  BANDCAMP_ROOM_H_