#include <sstream>
#include <iostream>
#include "include/tilemap.h"
#include "include/mazegenerationalgorithm.h"

//constants
constexpr int MAX_ROOM_SIZE = 15;
constexpr int MIN_ROOM_SIZE = 7;

//vars
SDL_Texture* image;
std::unordered_map<int, SDL_Rect> tiles;
/*
	0 - 
	1 - 
	2 - 
	3 - 
*/
int width;
int height;
int tilesize;
int cur_width;
int cur_height;
std::vector< std::vector < int > > map;

//constructor
Tilemap::Tilemap() {
	image = nullptr;
	width = 25;
	height = 18;
	tilesize = 32;
	rooms = {};
	cur_width = 0;
	cur_height = 0;
	srand(time(NULL));
}

/* Summary
 * Argument  
 *
*/
Tilemap::Tilemap(SDL_Texture* tex, int _width, int _height, int _tilesize) {
	image = tex;
	width = _width;
	height = _height;
	tilesize = _tilesize;
	rooms = {};
	cur_width = 0;
	cur_height = 0;
	srand(time(NULL));
}

//destructor
Tilemap::~Tilemap() {

}


//returns the map as 2d vector
std::vector< std::vector < int > > Tilemap::getMap() {
	return map;
}

std::vector< std::vector < int > >* Tilemap::getMapPtr() {
	return &map;
}

//setup tiles
void Tilemap::init() {
	map = std::vector<std::vector<int>>(height, std::vector<int>(width, 0));
	
	//ground tile
	tiles[0] = {0,0,tilesize,tilesize};
	//ceiling tile
	tiles[1] = {0,tilesize,tilesize,tilesize};
	//wall tile
	tiles[2] = {0,tilesize*2,tilesize,tilesize};
}

//sets the map
// takes a 2d vector
void Tilemap::setMap(std::vector< std::vector < int > > _map) {
	map = _map;
}

std::vector<Room*> Tilemap::getRooms() {
	return rooms;
}

//generates the map for our testroom
void Tilemap::genTestRoom() {
	//init to all floor
	map = std::vector<std::vector<int>>(height, std::vector<int>(width, 1));

	//just going to hardcode walls
	for(int row=0;row<height;row++) {
		map[row][0] = 2;
		map[row][width-1] = 2;
		map[row][width/2] = 2;
	}
	for(int col=0;col<width;col++) {
		map[0][col] = 2;
		map[height-1][col] = 2;
	}
	//lets put a hole in the wall so we can peep while the ooze asexually reproduces ;)
	map[height/2][width/2] = 1;
	
	map[4][4] = 4; //HardCoded door
}

void Tilemap::genTestTransitionRoom(){
	//init to all floor
	map = std::vector<std::vector<int>>(height, std::vector<int>(width, 1));

	for(int col = 0; col < width; col++){
		map[0][col] = 2; //Ceiling
		map[1][col] = 3; //Wall
		map[height-2][col] = 2; //Ceiling
		map[height-1][col] = 3; //Wall
	}
	
	for(int row = 0; row < height-1; row++){
		map[row][0] = 2;
		map[row][width-1] = 2;
	}
	
	for(int row = 0; row < height/4; row++){
		for(int col = width/4; col < (width*3/4); col++){
			map[row][col] = 2;
			map[row+1][col] = 3; //Ceiling
		}
	}
	
	map[4][14] = 1; //Space for the Warp Tile.
	map[5][14] = 1; //Space for the Door.
}

void Tilemap::genTestTransitionRoom2(){
	//init to all floor
	map = std::vector<std::vector<int>>(height, std::vector<int>(width, 1));

	for(int col = 0; col < width; col++){
		map[0][col] = 2; //Ceiling
		map[1][col] = 3; //Wall
		map[height-2][col] = 2; //Ceiling
		map[height-1][col] = 3; //Wall
	}
	
	for(int row = 0; row < height-1; row++){
		map[row][0] = 2;
		map[row][width-1] = 2;
	}
	
	for(int row = height*3/4; row < height-1; row++){
		for(int col = width/4; col < (width*3/4); col++){
			map[row][col] = 2;
		}
	}
	
	map[height*3/4][14] = 1; //Space for the Warp Tile.
}

std::vector<std::vector<int>> Tilemap::genMaze(){
	MGA * mga = new MGA((rand() % 20)+20, (rand() % 20)+20);
	return mga->getMaze();
}



//draw the tiles
SDL_Renderer* Tilemap::draw(SDL_Renderer* render, SDL_Rect cam) {
	for(int row=0;row<height;row++) {
		for(int col=0;col<width;col++) {
			//check if tile is floor or wall
			//0 = nothing
			//1 = ground
			//2 = wall
			SDL_Rect tile;
			if(map[row][col] == 1)
				tile = tiles[0]; //floor
			else if(map[row][col] == 2) 
				tile = tiles[1]; //ceiling
			else if(map[row][col] == 3)
				tile = tiles[2]; //wall
			else if(map[row][col] == 4)
				tile = tiles[0]; //door, uses ground tile
			if(map[row][col] != 0) {
				SDL_Rect dest = {(col*tilesize) - cam.x, (row*tilesize) - cam.y, tilesize, tilesize};
				SDL_RenderCopy(render, image, &tile, &dest);
			}
			//draw tile
			//SDL_Rect dest = {col*tilesize, row*tilesize, tilesize, tilesize};
			
		}
	}
	return render;
}

//Generates a random map by packing rooms
std::vector<std::vector<int>> Tilemap::genRandomMap() {
	Generator gen = Generator(width, height);
	for(int i=0;i<3;i++) {
		gen.placeRoom(gen.genRoom(MIN_ROOM_SIZE, MAX_ROOM_SIZE), false);
		//placeRoom(genRoom(MIN_ROOM_SIZE, MAX_ROOM_SIZE), true);
		
	}
	for(int i=0;i<5;i++) {
		gen.placeRoom(gen.genRoom(MIN_ROOM_SIZE, MAX_ROOM_SIZE), true);
		//
	}
	gen.finalize();
	return gen.getMap();
}

void Tilemap::printmap() {
	for(int r=0;r<map.size();r++) {
		for(int c=0;c<map[0].size();c++) {
			std::cout << map[r][c];
		}
		std::cout << std::endl;
	}
	std::cout << std::endl << cur_width << std::endl << cur_height << std::endl;

}