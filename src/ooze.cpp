#include "include/ooze.h"

// Default Constructor
Ooze::Ooze():state{roaming}, hostility{0} {}

//Constructor
//Ooze::Ooze(State st, int hostil) :state{st}, hostility{hostil} {}

//Destructor
Ooze::~Ooze(){};

void Ooze::increaseHostility() { if( hostility < 10 ) hostility++; }
void Ooze::decreaseHostility() { if( hostility >  0 ) hostility--; }

//returns width
int Ooze::getWidth() {
    return enemyRect.w;
}

//returns height
int Ooze::getHeight() {
    return enemyRect.h;
}

//returns x position
int Ooze::getX() {
    return enemyRect.x;
}

//returns y position
int Ooze::getY() {
    return enemyRect.y;
}

SDL_Rect* Ooze::getRect() {
    return &enemyRect;
}
