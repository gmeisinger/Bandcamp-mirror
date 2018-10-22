#include <SDL.h>

#include "include/ooze.h"
#include "include/spritesheet.h"
#include "include/utils.h"

SDL_Rect oozeRect;
SpriteSheet oozeSheet;
// Default Constructor
Ooze::Ooze():state{roaming}, hostility{0} {}

//Constructor from rect
Ooze::Ooze(SDL_Rect _rect):state{roaming}, hostility{0} {
    oozeRect = _rect;
    //Speed?
    //x_deltav = 0;
    //y_deltav = 0;
    //x_vel = 0;
    //y_vel = 0;
}

//Other constructor?
//Ooze::Ooze(State st, int hostil) :state{st}, hostility{hostil} {}

//Destructor
Ooze::~Ooze(){};

std::string Ooze::getInstanceName(){
	return "Ooze"; //There is only one ooze at a time for now.
}

void Ooze::input(const Uint8* keystate){}

//********TO DO:
//set ooze animation here, as per player.cpp
void Ooze::init(SDL_Renderer* gRenderer) {
	setSpriteSheet(utils::loadTexture(gRenderer, "res/ooze.png"), 3, 1);
}

void Ooze::setSpriteSheet(SDL_Texture* _sheet, int _cols, int _rows) {
    oozeSheet = SpriteSheet(_sheet);
    oozeSheet.setClips(_cols, _rows, oozeRect.w, oozeRect.h);
}

void Ooze::update(std::unordered_map<std::string, Object*> *objectList, Uint32 ticks){}

void Ooze::increaseHostility() { if( hostility < 10 ) hostility++; }
void Ooze::decreaseHostility() { if( hostility >  0 ) hostility--; }

SDL_Renderer* Ooze::draw(SDL_Renderer* renderer) {
    SDL_RenderCopy(renderer, oozeSheet.getTexture(), oozeSheet.get(0,0), getRect());
   return renderer;
}

bool Ooze::isUsed() {
	return true;
}

SpriteSheet Ooze::getSheet() {
    return oozeSheet;
}

//returns width
int Ooze::getWidth() {
    return oozeRect.w;
}

//returns height
int Ooze::getHeight() {
    return oozeRect.h;
}

//returns x position
int Ooze::getX() {
    return oozeRect.x;
}

//returns y position
int Ooze::getY() {
    return oozeRect.y;
}

SDL_Rect* Ooze::getRect() {
    return &oozeRect;
}
