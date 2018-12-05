#include "include/room.h"

Room::Room() {
	rect = {0,0,0,0};
	neighbors = {};
	intersect_rects = {};
	physics.init_room();
}

//constructor takes a rect
Room::Room(SDL_Rect _rect) {
	rect = _rect;
	neighbors = {};
	intersect_rects = {};
	physics.rand_room();
}

//destructor
Room::~Room() {

}

SDL_Rect* Room::getRect() {
	return &rect;
}

SDL_Rect Room::getRectCopy() {
	return rect;
}

SDL_Rect* Room::move(int _x, int _y) {
	rect.x = _x;
	rect.y = _y;
	return &rect;
}

void Room::addNeighbor(Room* room) {
	neighbors.push_back(room);
}

void Room::addIntersect(SDL_Rect rect) {
	intersect_rects.push_back(rect);
}

std::vector<Room*> Room::getNeighbors() {
	return neighbors;
}

std::vector<SDL_Rect> Room::getIntersects() {
	return intersect_rects;
}

bool Room::contains(SDL_Rect* _rect) {
	SDL_Rect _temp = {rect.x*32, rect.y*32, rect.w*32, rect.h*32};
	if(SDL_HasIntersection(_rect, &_temp)) {
		return true;
	}
	else return false;
}
