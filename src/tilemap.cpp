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
std::vector< std::vector < Tile* > > map;

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
std::vector< std::vector < Tile* > > Tilemap::getMap() {
	return map;
}

std::vector< std::vector < Tile* > >* Tilemap::getMapPtr() {
	return &map;
}

//setup tiles
void Tilemap::init() {
	map = std::vector<std::vector<Tile*>>(height, std::vector<Tile*>(width, new Tile()));
	
	//floor tile
	tiles["floor"] = {0,0,tilesize,tilesize};
	//ceiling tile
	tiles["ceiling"] = {0,tilesize,tilesize,tilesize};
	//wall tile
	tiles["wall"] = {0,tilesize*2,tilesize,tilesize};
}

//sets the map
// takes a 2d vector
void Tilemap::setMap(std::vector< std::vector < int > > _map) {
	map = convert(_map);
}

std::vector<Room*> Tilemap::getRooms() {
	return rooms;
}



void Tilemap::genTestTransitionRoom(){
	//init to all floor
	std::vector<std::vector<int>> intmap = std::vector<std::vector<int>>(height, std::vector<int>(width, 1));

	for(int col = 0; col < width; col++){
		intmap[0][col] = 2; //Ceiling
		intmap[1][col] = 3; //Wall
		intmap[height-2][col] = 2; //Ceiling
		intmap[height-1][col] = 3; //Wall
	}
	
	for(int row = 0; row < height-1; row++){
		intmap[row][0] = 2;
		intmap[row][width-1] = 2;
	}
	
	for(int row = 0; row < height/4; row++){
		for(int col = width/4; col < (width*3/4); col++){
			intmap[row][col] = 2;
			intmap[row+1][col] = 3; //Ceiling
		}
	}
	
	intmap[4][14] = 1; //Space for the Warp Tile.
	intmap[5][14] = 1; //Space for the Door.
	map = convert(intmap);
}

void Tilemap::genMaze(){
	MGA * mga = new MGA((rand() % 20)+20, (rand() % 20)+20);
	map = convert(mga->getMaze());
}



//draw the tiles
SDL_Renderer* Tilemap::draw(SDL_Renderer* render, SDL_Rect cam) {
	for(int row=0;row<height;row++) {
		for(int col=0;col<width;col++) {
			if(map[row][col]->isActive()) {
				Tile* t = map[row][col];
				SDL_Rect* src = t->getSource();
				SDL_Rect dest = {(col*tilesize) - cam.x, (row*tilesize) - cam.y, tilesize, tilesize};
				SDL_RenderCopy(render, image, src, &dest);
			}
		}
	}
	return render;
}

//Generates a random map by packing rooms
void Tilemap::genRandomMap() {
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
	map = convert(gen.getMap());
}

std::vector<std::vector<Tile*>> Tilemap::convert( std::vector<std::vector<int>> intmap) {

	for(int r=0;r<intmap.size();r++) {
		for(int c=0;c<intmap[0].size();c++) {
			if(intmap[r][c] == 1) {
				//floor tile
				map[r][c] = new Tile(tiles["floor"], {c*tilesize, r*tilesize, tilesize, tilesize});
			}
			else if(intmap[r][c] == 2) {
				// ceiling tile
				map[r][c] = new Tile(tiles["ceiling"], {c*tilesize, r*tilesize, tilesize, tilesize});
				map[r][c]->setBlocking(true);
			}
			else if(intmap[r][c] == 3) {
				// wall tile
				map[r][c] = new Tile(tiles["wall"], {c*tilesize, r*tilesize, tilesize, tilesize});
				map[r][c]->setBlocking(true);
			}
			else if(intmap[r][c] == 4) {
				// ceiling tile
				map[r][c] = new Tile(tiles["floor"], {c*tilesize, r*tilesize, tilesize, tilesize});
				map[r][c]->setDoor(true);
			}
			else {
				map[r][c] = new Tile();
			}
		}
	}
	return map;
}

void addObjects(std::unordered_map<std::string, Object*> *objectList) {

}
