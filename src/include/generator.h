#ifndef BANDCAMP_GENERATOR_H_
#define BANDCAMP_GENERATOR_H_

#include <SDL.h>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string>
#include <iostream>
#include <algorithm>
#include "room.h"

class Generator
{
private:
	int width;
	int height;
	int cur_width;
	int cur_height;
	std::vector< std::vector< int > > map;
	std::vector<SDL_Rect> rooms;
	std::vector<Room*> room_objs;
public:
	Generator();
	Generator(int w, int h);
	~Generator();
	std::vector< std::vector< int> > getMap();
	void placeRoom(SDL_Rect room, bool fill);
	SDL_Rect genRoom(int min, int max);
	std::vector<std::pair<int,int>> getCorners();
	bool checkOverlap(SDL_Rect room);
	bool growsMap(SDL_Rect room);
	int getNumRooms();
	void cutRoom(SDL_Rect room);
	void cutRoom(SDL_Rect room, int marker);
	void cutDoor(SDL_Rect intersect);
	void finalize();
	void setRoomNeighbors(Room* r);
	void addChests();
	std::vector<Room*> getRooms();
};

#endif  //  BANDCAMP_GENERATOR_H_