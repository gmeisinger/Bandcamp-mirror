/* Team Bandcamp
 * Class function: 
 * 
*/

#include <algorithm>
#include <vector>
#include <string>

#include "include/projectile.h"
#include "include/player.h"
#include "include/utils.h"
#include "include/testroom.h"

constexpr int FIRED_SPEED = 6;

SDL_Rect projRect; //The Collision Box
char projType;
//Image Stuff
SDL_Texture* projImg;
SDL_Rect projImgRect;
SDL_Rect projDrawBox;	//Where the Image is drawn on screen
Uint32 projTicks;
static int totalInstance = 0;//How many instances of the object exist?
int projNumber = 0;
bool projUsed;
bool spaceHeld = false;

//Constructor - takes a texture, width, height, proj type, and player
Projectile::Projectile(SDL_Rect _rect, char type, Player *player) {
    projRect = _rect;
	projDrawBox = _rect;
	projTicks = 0;
	projType = type;
	projPlayer = player;
	totalInstance++; //Increase instance Number
	projNumber = totalInstance;
	
	std::string s = "SPAWNED: "+getInstanceName();
	std::cout << s << std::endl;
	projUsed = false;
}

//Deconstructor
Projectile::~Projectile() {
}

Projectile::Projectile(){
	
}

void Projectile::input(const Uint8* keystate) {}

std::string Projectile::getInstanceName(){
	return "proj-"+std::to_string(projNumber);
}

void Projectile::init(SDL_Renderer *renderer){
	std::cout << "Projectile initiated" << std::endl;
	
	//Set up the right Image to display
	//Eventually these images might be global, rather than loaded every time it's spawned.
	projImg = utils::loadTexture(renderer, "res/rightProj.png");
	projImgRect.w = 32;
	projImgRect.h = 8;
	projImgRect.y = 0;
	
	switch(projType){
		//Tempurature
		case 'r':
			projImgRect.x = 0;
		break;
		
		//Oxygen
		case 'g':
			projImgRect.x = 32;
		break;
	}
}
		
void Projectile::update(std::unordered_map<std::string, Object*> *objectList, std::vector<std::vector<int>> grid, Uint32 ticks){
	updatePosition(ticks);
	checkProjOverlap(objectList);
}

SDL_Renderer* Projectile::draw(SDL_Renderer *renderer, SDL_Rect cam){
	//SDL_SetRenderDrawColor(renderer, 0x00, 0x30, 0x25, 0xFF);
	//SDL_RenderFillRect(renderer, &projRect);
	//get dest rect from player
	SDL_Rect* drawDest = new SDL_Rect;
	*drawDest = projDrawBox;
	drawDest->x -= 32;
	drawDest->y -= 16;
	//Draw the sprite
    SDL_RenderCopy(renderer, projImg, &projImgRect, drawDest);	
	return renderer;
}

void Projectile::updatePosition(Uint32 ticks){
	projTicks += ticks;
	if(projTicks > FIRED_SPEED) {
		projDrawBox.x = projRect.x + 1;
		projTicks = 0;
	}
}

//Checks if the player overlapped with the proj and acts accordingly
void Projectile::checkProjOverlap(std::unordered_map<std::string, Object*> *objectList) {
	/*
	bool overlap = projPlayer->getX() < projRect.x + projRect.w &&
				   projPlayer->getX() + projPlayer->getWidth() > projRect.x &&
				   projPlayer->getY() < projRect.y + projRect.h &&
				   projPlayer->getY() + projPlayer->getHeight() > projRect.y;

	if (overlap){//(xOverlap && yOverlap) {
		if (projType == 'e') {
			hud->currentTemp = std::min(100, hud->currentTemp+projValue);
			//std::cout << "TEMP UP!" << std::endl;
		} else if (projType == 'o') {
			hud->currentOxygen = std::min(100, hud->currentOxygen+projValue);
			//std::cout << "O2 UP!" << std::endl;
		} else {
			//left just in case we want some other types of projs later
		}
		
		//This only works because there is only one instance of this object. We will eventually have to 
		//make an ID system to Identify specific objects.
		//GOAL
		used = true;
		//objectList->erase(getInstanceName());
		//delete this;
	}
	*/
}

bool Projectile::isUsed() {
	return projUsed;
}

SDL_Rect* Projectile::getProjRect() {
    return &projRect;
}