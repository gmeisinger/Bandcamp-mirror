#ifndef BANDCAMP_TILE_H_
#define BANDCAMP_TILE_H_

#include <SDL.h>
#include <SDL_image.h>
#include <unordered_map>
#include <string>
#include <vector>

class Tile
{
private:
    SDL_Rect srcRect;
    SDL_Rect destRect;
    bool blocking;
    bool door;
    bool chest;
    bool active;
    bool visited;
    bool horWall;
public:
    Tile(SDL_Rect _srcRect, SDL_Rect _destRect);
    Tile();
    SDL_Rect* getSource();
    SDL_Rect* getDest();
    bool isBlocking();
    void setBlocking(bool b);
    bool isDoor();
    void setDoor(bool b);
    bool isChest();
    void setChest(bool b);
    void toggleBlocking();
    bool isActive();
    bool isVisited();
    void setVisited(bool v);
    bool isHorWall();
    void setHorWall(bool h);
};

#endif // BANDCAMP_TILE_H_
