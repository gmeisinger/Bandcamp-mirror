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
#include "tile.h"
#include "object.h"

class Tilemap
{
private:
	SDL_Texture* image;
	std::unordered_map<std::string, SDL_Rect> tiles;
	int width;
	int height;
	int tilesize;
	std::vector< std::vector < Tile* > > map;
	std::vector<Room*> rooms;
	int cur_width;
	int cur_height;
public:
	Tilemap(SDL_Texture* tex, int _width, int _height, int _tilesize);
	Tilemap();
	~Tilemap();
	std::vector< std::vector < Tile* > > getMap();
	std::vector< std::vector < Tile* > >& getMapRef();
	void setMap(std::vector< std::vector < int > > _map);
	void init();
	SDL_Renderer* draw(SDL_Renderer* render, SDL_Rect cam);
	std::vector<std::vector<Tile*>> convert(std::vector<std::vector<int>> intmap);
	void setNeighbors(Room* source);
	void genRandomMap();
	void addObjects(std::unordered_map<std::string, Object*> *objectList);
	//random map helpers
	std::vector<Room*> getRooms();
	Room* getRoom(int index);
	//std::vector< std::vector < int > > &getGrid();
	void genTestTransitionRoom();
	void genMaze();
};

#endif  //  BANDCAMP_TILEMAP_H_
