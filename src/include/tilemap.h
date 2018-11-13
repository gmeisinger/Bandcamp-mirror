#ifndef BANDCAMP_TILEMAP_H_
#define BANDCAMP_TILEMAP_H_

#include <SDL.h>
#include <unordered_map>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <time.h>
#include "room.h"
#include "generator.h"

class Tilemap
{
private:
	SDL_Texture* image;
	std::unordered_map<int, SDL_Rect> tiles;
	int width;
	int height;
	int tilesize;
	std::vector< std::vector < int > > map;
	std::vector<Room*> rooms;
	int cur_width;
	int cur_height;
public:
	Tilemap(SDL_Texture* tex, int _width, int _height, int _tilesize);
	Tilemap();
	~Tilemap();
	std::vector< std::vector < int > > getMap();
	std::vector< std::vector < int > >* getMapPtr();
	void setMap(std::vector< std::vector < int > > _map);
	void genTestRoom();
	void init();
	SDL_Renderer* draw(SDL_Renderer* render, SDL_Rect cam);
	void finalize();
	void setNeighbors(Room* source);
	std::vector<std::vector<int>> genRandomMap();
	//random map helpers
	std::vector<Room*> getRooms();
	void printmap();
	//std::vector< std::vector < int > > &getGrid();
	void genTestTransitionRoom();
	void genTestTransitionRoom2();
	void genMaze();
};

#endif  //  BANDCAMP_TILEMAP_H_
