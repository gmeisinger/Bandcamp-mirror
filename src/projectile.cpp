/* Team Bandcamp
 * Class function: 
 * 
*/

#include "include/projectile.h"

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

Projectile::Projectile(char type, int playerX, int playerY) {
	switch(type){
		case 'n':
			projRect = {playerX + 12, playerY - 32, 8, 32};
			projDrawBox = {412, 268, 8, 32};
			break;
		case 'e':
			projRect = {playerX - 32, playerY + 12, 32, 8};
			projDrawBox = {368, 312, 32, 8};
			break;
		case 's':
			projRect = {playerX + 12, playerY + 32, 8, 32};
			projDrawBox = {412, 332, 8, 32};
			break;
		case 'w':
			projRect = {playerX + 32, playerY + 12, 32, 8};
			projDrawBox = {432, 312, 32, 8};
			break;
	}
	projTicks = 0;
	projType = type;
	totalInstance++; //Increase instance Number
	projNumber = totalInstance;
	up = false;
	down = false;
	left = false;
	right = false;
	projUsed = false;
	//std::cout << s << std::endl;
}

//Deconstructor
Projectile::~Projectile() {
}

Projectile::Projectile(){
	
}

void Projectile::input(const Uint8* keystate) {
	up = keystate[SDL_SCANCODE_W];
	left = keystate[SDL_SCANCODE_A];
	down = keystate[SDL_SCANCODE_S];
	right = keystate[SDL_SCANCODE_D];
}

std::string Projectile::getInstanceName(){
	return "proj-"+std::to_string(projNumber);
}

void Projectile::init(SDL_Renderer *renderer){
	//std::cout << getInstanceName() << " initiated" << std::endl;
	
	//Set up the right Image to display
	//Eventually these images might be global, rather than loaded every time it's spawned.
	projImg = utils::loadTexture(renderer, "res/projectiles.png");
	
	switch(projType){
		case 'n':
			projImgRect.x = 0;
			projImgRect.y = 0;
			projImgRect.w = 8;
			projImgRect.h = 32;
			break;
		case 'e':
			projImgRect.x = 48;
			projImgRect.y = 0;
			projImgRect.w = 32;
			projImgRect.h = 8;
			break;
		case 's':
			projImgRect.x = 40;
			projImgRect.y = 0;
			projImgRect.w = 8;
			projImgRect.h = 32;
			break;
		case 'w':
			projImgRect.x = 8;
			projImgRect.y = 0;
			projImgRect.w = 32;
			projImgRect.h = 8;
			break;
	}
}
		
void Projectile::update(std::unordered_map<std::string, Object*> &objectList, std::vector<std::vector<Tile*>> &grid, Uint32 ticks){
	updatePosition(ticks);
	checkProjOverlap(projRect.x, projRect.y, grid);
}

SDL_Renderer* Projectile::draw(SDL_Renderer *renderer, SDL_Rect cam) {
	SDL_Rect* drawDest = new SDL_Rect;
	*drawDest = projDrawBox;
	//Draw the sprite
    SDL_RenderCopy(renderer, projImg, &projImgRect, drawDest);	
	return renderer;
}

void Projectile::updatePosition(Uint32 ticks){
	projTicks += ticks;
	if(projTicks > 2) {
		switch(projType){
		case 'n':
			projRect.y = projRect.y - FIRED_SPEED;
			projDrawBox.y = projDrawBox.y - FIRED_SPEED;
			break;
		case 'e':
			projRect.x = projRect.x - FIRED_SPEED;
			projDrawBox.x = projDrawBox.x - FIRED_SPEED;
			break;
		case 's':
			projRect.y = projRect.y + FIRED_SPEED;
			projDrawBox.y = projDrawBox.y + FIRED_SPEED;
			break;
		case 'w':
			projRect.x = projRect.x + FIRED_SPEED;
			projDrawBox.x = projDrawBox.x + FIRED_SPEED;
			break;
		}
		if (up) {
			projDrawBox.y = projDrawBox.y + 2;
		}
		if (left) {
			projDrawBox.x = projDrawBox.x + 2;
		}
		if (down) {
			projDrawBox.y = projDrawBox.y - 2;
		}
		if (right) {
			projDrawBox.x = projDrawBox.x - 2;
		}
		projTicks = 0;
	}
}

void Projectile::checkProjOverlap(int curX, int curY, std::vector<std::vector<int>> grid) {
	if(collision::checkColLeft(projRect, grid, 32) || collision::checkColRight(projRect, grid, 32) || 
	   collision::checkColTop(projRect, grid, 32) || collision::checkColBottom(projRect, grid, 32)) {
		  projUsed = true;
    }
}

bool Projectile::isUsed() {
	return projUsed;
}

SDL_Rect* Projectile::getProjRect() {
    return &projRect;
}