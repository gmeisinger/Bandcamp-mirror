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
    Room2 physics;
    bool contains(SDL_Rect* _rect);
};

#endif  //  BANDCAMP_ROOM_H_
