#ifndef BANDCAMP_WARPTILE_H_
#define BANDCAMP_WARPTILE_H_

#include <vector>
#include <unordered_map>

#include "game.h"
#include "utils.h"
#include "object.h"

class WarpTile : public Object
{
private:
    SpriteSheet sheet;
    SDL_Texture* img;
    SDL_Rect collRect, drawRect; //The Collision Box and Draw Box
    int instanceNumber = 0;
    int x_pos, y_pos; //X and Y according to the TILEMAP
    bool insideWall; //Asthetically, should the warp tile be covered up by a ceiling tile?
    int destX, destY; //If you are warping to somewhere on the screen, note it here
    int destScreen; //If you are warping to a different screen, note it here
    bool fade; //If you want a fade transition, note it here
    SDL_Renderer* reference; //When you init the fadeObj, you need a reference to the sdl_renderer
    SDL_Rect* getRect();
    
public:
    void input(const Uint8* keystate);
    void init(SDL_Renderer *renderer);
    void update(std::unordered_map<std::string, Object*> &objectList, std::vector<std::vector<Tile*>> &grid, Uint32 ticks);
    std::string getInstanceName();
    SDL_Renderer* draw(SDL_Renderer *renderer, SDL_Rect cam);
    bool collision(Player*& playerObj);
    bool isUsed();
    WarpTile();
    ~WarpTile();
    WarpTile(int x, int y); //Defaults in warping you to the 1st screen (currently the menu screen)
    WarpTile(int x, int y, bool _insideWall, bool _fade, int _destScreen); //Screen Warp
    WarpTile(int x, int y, bool _insideWall, bool _fade, int _destX, int destY); //X/Y Warp
};

#endif  //  BANDCAMP_WARPTILE_H_
