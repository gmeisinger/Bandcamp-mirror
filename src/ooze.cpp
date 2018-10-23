#include <SDL.h>

#include "include/ooze.h"
#include "include/spritesheet.h"
#include "include/utils.h"
#include "include/HUD.h"


//SDL_Rect rect;
//SpriteSheet sheet;

//initialize static member variables
int Ooze::totalOoze = 0;

// Default Constructor
Ooze::Ooze():state{roaming}, hostility{0} {}

//Constructor from rect
Ooze::Ooze(SDL_Rect _rect, Player *player, HUD *h):state{roaming}, hostility{0} {
    rect = _rect;
    oozePlayer = player;
	hud = h;
	totalOoze++; //Increase # of instances counter
	oozeNumber = totalOoze;
    //Speed
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
	return "Ooze-"+std::to_string(oozeNumber);
}

void Ooze::input(const Uint8* keystate){}

//********TO DO:
//set ooze animation here, as per player.cpp
void Ooze::init(SDL_Renderer* gRenderer) {
	setSpriteSheet(utils::loadTexture(gRenderer, "res/ooze.png"), 3, 1);
    addAnimation("wandering", Animation(getSheet().getRow(0)));
    setAnimation("wandering");
}

void Ooze::setSpriteSheet(SDL_Texture* _sheet, int _cols, int _rows) {
    sheet = SpriteSheet(_sheet);
    sheet.setClips(_cols, _rows, rect.w, rect.h);
}

//*********TO DO:
//update motion here
void Ooze::update(std::unordered_map<std::string, Object*> *objectList, Uint32 ticks) {
	checkOozeOverlap(objectList);
    
    //update animation
    updateAnimation(ticks);
}

void Ooze::increaseHostility() {
	if (hostility < 10)
		hostility++;
}
void Ooze::decreaseHostility() {
	if (hostility >  0)
		hostility--;
}

SDL_Renderer* Ooze::draw(SDL_Renderer* renderer) {
    SDL_RenderCopy(renderer, sheet.getTexture(), sheet.get(0,0), getRect());
   return renderer;
}

//Checks if the player overlapped with the ooze and acts accordingly
//based on pickup's method
void Ooze::checkOozeOverlap(std::unordered_map<std::string, Object*> *objectList) {
	bool overlap = oozePlayer->getX() < rect.x + rect.w &&
				   oozePlayer->getX() + oozePlayer->getWidth() > rect.x &&
				   oozePlayer->getY() < rect.y + rect.h &&
				   oozePlayer->getY() + oozePlayer->getHeight() > rect.y;

	if (overlap) {
		hud->currentHealth = std::max(0, hud->currentHealth-damage);
        //Player->speed = Player->speed / 2;
        //void Player->updateVelocity(int _xdv, int _ydv); //would this work?
		std::string s = "HIT: "+getInstanceName();
		std::cout << s << std::endl;
	}
}

void Ooze::updateAnimation(Uint32 ticks) {

    if(true) { //ticks/10%2 == 2
        setAnimation("wandering");
        anim->play();
    }
    else {
        anim->reset();
        anim->stop();
    }
    anim->update(ticks);
}

bool Ooze::isUsed() { return false; }

Animation* Ooze::getAnimation(std::string tag) { return &anims[tag]; }

void Ooze::setAnimation(std::string tag) { anim = &anims[tag]; }

void Ooze::addAnimation(std::string tag, Animation anim) { anims[tag] = anim; }

SpriteSheet Ooze::getSheet() { return sheet; }

//returns width
int Ooze::getWidth() { return rect.w; }

//returns height
int Ooze::getHeight() { return rect.h; }

//returns x position
int Ooze::getX() { return rect.x; }

//returns y position
int Ooze::getY() { return rect.y; }

SDL_Rect* Ooze::getRect() { return &rect; }
