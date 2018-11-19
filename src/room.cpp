#include "include/room.h"

Room::Room() {
	rect = {0,0,0,0};
	neighbors = {};
	intersect_rects = {};
}

//constructor takes a rect
Room::Room(SDL_Rect _rect) {
	rect = _rect;
	neighbors = {};
	intersect_rects = {};
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
