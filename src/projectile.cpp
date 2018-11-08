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

Projectile::Projectile(SDL_Rect _rect, char type, int playerX, int playerY) {
    projRect = _rect;
	projRect.x = playerX;
	projRect.y = playerY;
	projDrawBox = _rect;
	projDrawBox.x = playerX;
	projDrawBox.y = playerY;
	projTicks = 0;
	projType = type;
	totalInstance++; //Increase instance Number
	projNumber = totalInstance;
	//std::string s = "SPAWNED: "+getInstanceName();
	//std::cout << s << std::endl;
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
	//std::cout << getInstanceName() << " initiated" << std::endl;
	
	//Set up the right Image to display
	//Eventually these images might be global, rather than loaded every time it's spawned.
	projImg = utils::loadTexture(renderer, "res/rightProj.png");
	projImgRect.w = 32;
	projImgRect.h = 8;
	projImgRect.y = 0;
	
	switch(projType){
		case 'r':
			projImgRect.x = 0;
			break;
		case 'g':
			projImgRect.x = 32;
			break;
	}
}
		
void Projectile::update(std::unordered_map<std::string, Object*> *objectList, std::vector<std::vector<int>> grid, Uint32 ticks){
	updatePosition(ticks);
	checkProjOverlap(projRect.x, projRect.y, grid);
}

SDL_Renderer* Projectile::draw(SDL_Renderer *renderer, SDL_Rect cam){
	//SDL_SetRenderDrawColor(renderer, 0x00, 0x30, 0x25, 0xFF);
	//SDL_RenderFillRect(renderer, &projRect);
	//std::cout << getInstanceName() << " drawn" << std::endl;
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
		//std::cout << getInstanceName() << " moved" << std::endl;
		projRect.x = projRect.x + 1;
		projDrawBox.x = projDrawBox.x + 1;
		projTicks = 0;
	}
}

void Projectile::checkProjOverlap(int curX, int curY, std::vector<std::vector<int>> grid) {
	if(collision::checkCol(projRect, grid, 32)) {
        projRect.x = curX;
		projUsed = true;
    }
    if(collision::checkCol(projRect, grid, 32)) {
        projRect.y = curY;
        projUsed = true;
    }
}

bool Projectile::isUsed() {
	return projUsed;
}

SDL_Rect* Projectile::getProjRect() {
    return &projRect;
}