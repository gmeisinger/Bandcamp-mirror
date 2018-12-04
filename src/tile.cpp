#include "include/tile.h"

Tile::Tile(SDL_Rect _srcRect, SDL_Rect _destRect) {
	srcRect = _srcRect;
	destRect = _destRect;
	blocking = false;
	door = false;
	active = true;
	visited = false;
}

Tile::Tile() {
	srcRect = {0,0,0,0};
	destRect = {0,0,0,0};
	blocking = false;
	door = false;
	active = false;
}

SDL_Rect* Tile::getSource() {
	return &srcRect;
}

SDL_Rect* Tile::getDest() {
	return &destRect;
}

bool Tile::isBlocking() {
	return blocking;
}

void Tile::setBlocking(bool b) {
	blocking = b;
}

bool Tile::isDoor() {
	return door;
}

void Tile::setDoor(bool b) {
	door = b;
}

bool Tile::isVisited() {
	return visited;
}

void Tile::setVisited(bool v) {
	visited = v;
}

void Tile::toggleBlocking() {
	if(blocking) blocking = false;
	else blocking = true;
}

bool Tile::isActive() {
	return active;
}