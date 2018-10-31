#include "include/tilemap.h"

//constants

//vars
SDL_Texture* image;
std::unordered_map<int, SDL_Rect> tiles;
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

//setup tiles
void Tilemap::init() {
	grid = std::vector<std::vector<int>>(height, std::vector<int>(width, 1));
	//just going to hardcode testroom
	for(int row=0;row<height;row++) {
		grid[row][0] = 2;
		grid[row][width-1] = 2;
	}
	for(int col=0;col<width;col++) {
		grid[0][col] = 2;
		grid[height-1][col] = 2;
	}
	//ground tile
	tiles[0] = {0,0,tilesize,tilesize};
	//wall tiles based on bitmasking
	tiles[6] = {tilesize,0,tilesize,tilesize};
	tiles[10] = {2*tilesize,0,tilesize,tilesize}; //n but could be s
	tiles[12] = {3*tilesize,0,tilesize,tilesize};
	tiles[5] = {tilesize,tilesize,tilesize,tilesize}; //w but could be e
	//tiles["e_wall"] = {3*tilesize,tilesize,tilesize,tilesize};//e but could be w
	tiles[3] = {tilesize,2*tilesize,tilesize,tilesize};
	//tiles["s_wall"] = {2*tilesize,2*tilesize,tilesize,tilesize};//s but could be n
	tiles[9] = {3*tilesize,2*tilesize,tilesize,tilesize};
}

int Tilemap::getMask(int row, int col) {
	int bmask = 0;
	if(row > 0 && grid[row-1][col] == 2) {
		bmask += 1;
	}
	if(col < (width-1) && grid[row][col+1] == 2) {
		bmask += 2;
	}
	if(row < (height-1) && grid[row+1][col] == 2) {
		bmask += 4;
	}
	if(col > width && grid[row][col-1] == 2) {
		bmask += 8;
	}
	return bmask;
}

SDL_Rect Tilemap::getWall(int row, int col) {
	//gonna use some bitmasking to get the right wall tile
	int mask = getMask(row, col);
	
	//need to deal with n/s e/w
	return tiles[mask];
}

/*use bit masking to get correct wall tiles
void Tilemap::setWalls() {
	for(int row=0;row<height;row++) {
		for(int col=0;col<width;col++) {
			if(grid[row][col] == 0) {
				//floor
				
			}
			else if(grid[row][col] == 1) {
				//wall
				tile = getWall(row, col);
			}
			//draw tile
		}
	}
}*/

//draw the tiles
SDL_Renderer* Tilemap::draw(SDL_Renderer* render) {
	for(int row=0;row<height;row++) {
		for(int col=0;col<width;col++) {
			//check if tile is floor or wall
			SDL_Rect tile;
			if(grid[row][col] == 1) {
				//floor
				tile = tiles[0];
			}
			else if(grid[row][col] == 2) {
				//wall
				tile = getWall(row, col);
			}
			//draw tile
			SDL_Rect dest = {col*tilesize, row*tilesize, tilesize, tilesize};
			SDL_RenderCopy(render, image, &tile, &dest);
		}
	}
	return render;
}