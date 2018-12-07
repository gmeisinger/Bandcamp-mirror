/* Team Bandcamp
 * Class function:
 * The class that handles door operations
 */

#include "include/warptile.h"
#include "include/fadeobj.h"

static int totalInstance = 0; //How many instances of the object exist?

//Constructor
//X and Y are in terms of the TILE MAP

//If you want the warp tile to warp you somewhere in the room.
WarpTile::WarpTile(int x, int y, bool _insideWall, bool _fade, int _destX, int _destY) {
    x_pos = x;
    y_pos = y;
    collRect = {x*TILE_SIZE+(TILE_SIZE/4), y*TILE_SIZE+(TILE_SIZE/4), TILE_SIZE/2, TILE_SIZE/2};
    totalInstance++; //Increase instance Number
    instanceNumber = totalInstance;
    insideWall = _insideWall;
    fade = _fade;
    destScreen = -1;
    destX = _destX;
    destY = _destY;
}

WarpTile::WarpTile(int x, int y, bool _insideWall, bool _fade, int _destScreen) {
    x_pos = x;
    y_pos = y;
    collRect = {x*TILE_SIZE+(TILE_SIZE/4), y*TILE_SIZE+(TILE_SIZE/4), TILE_SIZE/2, TILE_SIZE/2};
    totalInstance++; //Increase instance Number
    instanceNumber = totalInstance;
    insideWall = _insideWall;
    fade = _fade;
    destScreen = _destScreen;
    destX = -1;
    destY = -1;
}

//X and Y are in terms of the TILE MAP
WarpTile::WarpTile(int x, int y) {
    x_pos = x;
    y_pos = y;
    collRect = {x*TILE_SIZE+(TILE_SIZE/4), y*TILE_SIZE+(TILE_SIZE/4), TILE_SIZE/2, TILE_SIZE/2};
    totalInstance++; //Increase instance Number
    instanceNumber = totalInstance;
    insideWall = false;
    fade = false;
    destScreen = 0; //By default it takes you back to the first screen.
    destX = -1;
    destY = -1;
}

//Deconstructor
WarpTile::~WarpTile() {}

WarpTile::WarpTile(){}

void WarpTile::input(const Uint8* keystate){}

std::string WarpTile::getInstanceName(){
    std::ostringstream ss;
    ss << instanceNumber;
    return "WarpTile-"+ss.str();
}

void WarpTile::init(SDL_Renderer* gRenderer){
    //set up WarpTile sprite
    img = utils::loadTexture(gRenderer, "res/map_tiles.png");
    if(insideWall)
        drawRect = {0,TILE_SIZE,TILE_SIZE,TILE_SIZE}; //The Ceiling Tile
    else
        drawRect = {0,TILE_SIZE*3,TILE_SIZE,TILE_SIZE}; //"Warp" Tile
    
    reference = gRenderer; //For initing the FadeObj
}

void WarpTile::update(std::unordered_map<std::string, Object*> &objectList, std::vector<std::vector<Tile*>> &grid, Uint32 ticks){
    Player * p;
    
    auto it = objectList.find("player");
    if (it != objectList.end())
        p = static_cast<Player*>(it->second);
    
    if(collision(p)){
        if(destX != -1){
            p->getRect()->x = destX;
            p->getRect()->y = destY;
        }
        else if(destScreen != -1){
            if(fade){
                FadeObj* f = new FadeObj(destScreen);
                f->init(reference);
                objectList.insert({"FadeObj", f}); //Fade out the screen
            }
            else
                GSM::currentScreen = destScreen;
        }
    }
}

bool WarpTile::collision(Player*& playerObj){
    //Also check direction of the player later
    SDL_Rect * playerRect = playerObj->getRect();
    
    return playerRect->x < collRect.x + collRect.w &&
    playerRect->x + playerRect->w > collRect.x &&
    playerRect->y < collRect.y + collRect.h &&
    playerRect->y + playerRect->h > collRect.y;
}

SDL_Renderer* WarpTile::draw(SDL_Renderer *renderer, SDL_Rect cam){
    SDL_Rect* dest = new SDL_Rect;
    *dest = collRect;
    dest->x -= cam.x+TILE_SIZE/4;
    dest->y -= cam.y+TILE_SIZE/4;
    dest->h = TILE_SIZE;
    dest->w = TILE_SIZE;
    SDL_RenderCopy(renderer, img, &drawRect, dest);
    return renderer;
}

bool WarpTile::isUsed(){return false;}

SDL_Rect* WarpTile::getRect(){return NULL;}
