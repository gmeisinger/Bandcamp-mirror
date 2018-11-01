#ifndef BANDCAMP_TILEMAP_H_
#define BANDCAMP_TILEMAP_H_

#include <SDL.h>
#include <unordered_map>
#include <vector>
#include <string>

class Tilemap
{
private:
	SDL_Texture* image;
	std::unordered_map<int, SDL_Rect> tiles;
	int width;
	int height;
	int tilesize;
	std::vector< std::vector < int > > grid;
public:
	Tilemap(SDL_Texture* tex, int _width, int _height, int _tilesize);
	Tilemap();
	~Tilemap();
	std::vector< std::vector < int > > getGrid();
	void setGrid(std::vector< std::vector < int > > _grid);
	void genTestRoom();
	void init();
	SDL_Renderer* draw(SDL_Renderer* render);
};

#endif  //  BANDCAMP_TILEMAP_H_