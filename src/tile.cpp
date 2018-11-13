#include "tile.h"

Tile::Tile(SDL_Rect _srcRect, SDL_Rect _destRect) {
	srcRect = _srcRect;
	destRect = _destRect;
	blocking = false;
	door = false;
}

Tile::~Tile() {}

SDL_Rect getSource() {
	return &srcRect;
}

SDL_Rect getDest() {
	return &destRect;
}

bool isBlocking() {
	return blocking;
}

void setBlocking(bool b) {
	blocking = b;
}

bool isDoor() {
	return door;
}

void setDoor(bool b) {
	door = b;
}

void toggleBlocking() {
	if(blocking) blocking = false;
	else blocking = true;
}