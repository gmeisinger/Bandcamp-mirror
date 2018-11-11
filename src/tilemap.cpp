#include "include/tilemap.h"

//constants
constexpr int MAX_ROOM_SIZE = 15;
constexpr int MIN_ROOM_SIZE = 7;
void printthis(SDL_Rect* r, std::string s);

//vars
SDL_Texture* image;
std::unordered_map<int, SDL_Rect> tiles;
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

//setup tiles
void Tilemap::init() {
	map = std::vector<std::vector<int>>(height, std::vector<int>(width, 0));
	
	//ground tile
	tiles[0] = {0,0,tilesize,tilesize};
	//wall tile
	tiles[1] = {0,tilesize,tilesize,tilesize};
}

//returns the map as 2d vector
std::vector< std::vector < int > > Tilemap::getMap() {
	return map;
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
	map[height/2][width/2] = 1;
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
			if(map[row][col] == 1) {
				//floor
				tile = tiles[0];
			}
			else if(map[row][col] == 2) {
				//wall
				tile = tiles[1];
			}

			//draw tile
			//SDL_Rect dest = {col*tilesize, row*tilesize, tilesize, tilesize};
			SDL_Rect dest = {(col*tilesize) - cam.x, (row*tilesize) - cam.y, tilesize, tilesize};
			SDL_RenderCopy(render, image, &tile, &dest);
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

void printthis(SDL_Rect* r, std::string s) {
	std::cout << s << " = " << r->x << " " << r->y << " " << r->w << " " << r->h << std::endl;
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