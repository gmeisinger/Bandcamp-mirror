#include <sstream>
#include <iostream>
#include "include/tilemap.h"
#include "include/mazegenerationalgorithm.h"

//constants

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
std::vector< std::vector < int > > grid;

//constructor
Tilemap::Tilemap() {
	image = nullptr;
	width = 25;
	height = 18;
	tilesize = 32;
}

Tilemap::Tilemap(SDL_Texture* tex, int _width, int _height, int _tilesize) {
	image = tex;
	width = _width;
	height = _height;
	tilesize = _tilesize;
}

//destructor
Tilemap::~Tilemap() {

}

//returns the grid as 2d vector
std::vector< std::vector < int > > & Tilemap::getGrid() {
	return grid;
}

//sets the grid
// takes a 2d vector
void Tilemap::setGrid(std::vector< std::vector < int > > _grid) {
	grid = _grid;
}

//generates the grid for our testroom
void Tilemap::genTestRoom() {
	//init to all floor
	grid = std::vector<std::vector<int>>(height, std::vector<int>(width, 1));

	//just going to hardcode walls
	for(int row=0;row<height;row++) {
		grid[row][0] = 2;
		grid[row][width-1] = 2;
		grid[row][width/2] = 2;
	}
	for(int col=0;col<width;col++) {
		grid[0][col] = 2;
		grid[height-1][col] = 2;
	}
	//lets put a hole in the wall so we can peep while the ooze asexually reproduces ;)
	grid[height/2][width/2] = 1;
	
	grid[4][4] = 4; //HardCoded door
}

void Tilemap::genTestTransitionRoom(){
	//init to all floor
	grid = std::vector<std::vector<int>>(height, std::vector<int>(width, 1));

	for(int col = 0; col < width; col++){
		grid[0][col] = 2; //Ceiling
		grid[1][col] = 3; //Wall
		grid[height-2][col] = 2; //Ceiling
		grid[height-1][col] = 3; //Wall
	}
	
	for(int row = 0; row < height-1; row++){
		grid[row][0] = 2;
		grid[row][width-1] = 2;
	}
	
	for(int row = 0; row < height/4; row++){
		for(int col = width/4; col < (width*3/4); col++){
			grid[row][col] = 2;
			grid[row+1][col] = 3; //Ceiling
		}
	}
	
	grid[4][14] = 1; //Space for the Warp Tile.
	grid[5][14] = 1; //Space for the Door.
}

void Tilemap::genTestTransitionRoom2(){
	//init to all floor
	grid = std::vector<std::vector<int>>(height, std::vector<int>(width, 1));

	for(int col = 0; col < width; col++){
		grid[0][col] = 2; //Ceiling
		grid[1][col] = 3; //Wall
		grid[height-2][col] = 2; //Ceiling
		grid[height-1][col] = 3; //Wall
	}
	
	for(int row = 0; row < height-1; row++){
		grid[row][0] = 2;
		grid[row][width-1] = 2;
	}
	
	for(int row = height*3/4; row < height-1; row++){
		for(int col = width/4; col < (width*3/4); col++){
			grid[row][col] = 2;
		}
	}
	
	grid[height*3/4][14] = 1; //Space for the Warp Tile.
}

void Tilemap::genMaze(){
	MGA * mga = new MGA((rand() % 20)+20, (rand() % 20)+20);
	grid = mga->getMaze();
}

//setup tiles
void Tilemap::init() {
	grid = std::vector<std::vector<int>>(height, std::vector<int>(width, 0));
	
	//ground tile
	tiles[0] = {0,0,tilesize,tilesize};
	//ceiling tile
	tiles[1] = {0,tilesize,tilesize,tilesize};
	//wall tile
	tiles[2] = {0,tilesize*2,tilesize,tilesize};
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
			if(grid[row][col] == 1)
				tile = tiles[0]; //floor
			else if(grid[row][col] == 2) 
				tile = tiles[1]; //ceiling
			else if(grid[row][col] == 3)
				tile = tiles[2]; //wall

			//draw tile
			//SDL_Rect dest = {col*tilesize, row*tilesize, tilesize, tilesize};
			SDL_Rect dest = {(col*tilesize) - cam.x, (row*tilesize) - cam.y, tilesize, tilesize};
			SDL_RenderCopy(render, image, &tile, &dest);
		}
	}
	return render;
}