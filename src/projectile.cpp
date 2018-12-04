/* Team Bandcamp
 * Class function: 
 * 
*/

#include "include/projectile.h"


constexpr int FIRED_SPEED = 6;

static int totalInstance = 0;//How many instances of the object exist?

Projectile::Projectile(char type, int playerX, int playerY) {
	switch(type){
		case 'n':
			projRect = {playerX + 12, playerY + 8, 8, 32};
			projDrawBox = {412, 308, 8, 32};
			break;
		case 'e':
			projRect = {playerX + 8, playerY + 12, 32, 8};
			projDrawBox = {408, 312, 32, 8};
			break;
		case 's':
			projRect = {playerX + 12, playerY - 8, 8, 32};
			projDrawBox = {412, 292, 8, 32};
			break;
		case 'w':
			projRect = {playerX - 8, playerY + 12, 32, 8};
			projDrawBox = {392, 312, 32, 8};
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
	playerXVel = 0;
	playerYVel = 0;
	correction = {0,0,0,0};
}

//Deconstructor
Projectile::~Projectile() {}

Projectile::Projectile() {}

void Projectile::input(const Uint8* keystate) {}

std::string Projectile::getInstanceName(){
	std::ostringstream ss;
	ss << projNumber;
	return "proj-"+ss.str();
}

void Projectile::init(SDL_Renderer *renderer) {
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
	
	rendererReference = renderer;
}
		
void Projectile::update(std::unordered_map<std::string, Object*> &objectList, std::vector<std::vector<Tile*>> &grid, Uint32 ticks){
	std::cout << "Entered Projectile update" << std::endl;
	updatePosition(ticks);
	checkProjOverlap(objectList, grid);
	std::cout << "Exited Projectile update" << std::endl;
}

SDL_Renderer* Projectile::draw(SDL_Renderer *renderer, SDL_Rect cam) {
	if (cam.x >= -2 && cam.x <= 2 && cam.y >= -2 && cam.y <= 2 && cam.w == 0 && cam.h == 0) {
		correction = cam;
	} else {
		SDL_Rect* drawDest = new SDL_Rect;
		*drawDest = projDrawBox;
		SDL_RenderCopy(renderer, projImg, &projImgRect, drawDest);
	}
	return renderer;
}

void Projectile::updatePosition(Uint32 ticks) {
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
		projDrawBox.x = projDrawBox.x - correction.x;
		projDrawBox.y = projDrawBox.y - correction.y;
		projTicks = 0;
	}
}

void Projectile::checkProjOverlap(std::unordered_map<std::string, Object*> &objectList, std::vector<std::vector<Tile*>> &grid) {
	std::unordered_map<std::string, Object*>::iterator it = objectList.begin();
	while(it != objectList.end()) {
		if(it->second->getInstanceName().find("ooze") != -1) {
			if (collision::checkCol(projRect, *(it->second->getRect()))) {
				projUsed = true;
				break;
			}
		}
		it++;
	}
	
	if (!projUsed) {
		if(collision::checkColLeft(projRect, grid, 32) || collision::checkColRight(projRect, grid, 32) ||
		   collision::checkColTop(projRect, grid, 32) || collision::checkColBottom(projRect, grid, 32)) {
			Breach* newBreach = new Breach(projType, projRect, projDrawBox);
			newBreach->init(rendererReference);
			objectList[newBreach->getInstanceName()] = newBreach;
			projUsed = true;
		}
	}
}

bool Projectile::isUsed() {
	return projUsed;
}

SDL_Rect* Projectile::getRect() {
    return &projRect;
}
