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

void Tilemap::init() {
	grid = new std::vector<std::vector<int>>(height, std::vector<int>(width, 0));
	//ground tile
	tiles[0] = {0,0,tilesize,tilesize};
}

//draw the tiles
SDL_Renderer* draw(SDL_Renderer* render) {
	for(int row=0;row<height;row++) {
		for(int col=0;col<width;col++) {

		}
	}
}