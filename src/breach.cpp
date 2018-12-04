/* Team Bandcamp
 * Class function: 
 * 
*/

#include "include/breach.h"

Uint32 bTicks;
static int totalInstance = 0;

Breach::Breach(char type, SDL_Rect rect, SDL_Rect drawBox) {
	bRect = rect;
	bDrawBox = drawBox;
	switch(type) {
		case 'n':
			bRect.y = bRect.y - 32;
			bDrawBox.y = bDrawBox.y - 32;
			break;
		case 'e':
			bRect.x = bRect.x - 32;
			bDrawBox.x = bDrawBox.x - 32;
			break;
		case 's':
			bRect.y = bRect.y + 32;
			bDrawBox.y = bDrawBox.y + 32;
			break;
		case 'w':
			bRect.x = bRect.x + 32;
			bDrawBox.x = bDrawBox.x + 32;
			break;
	}
	bTicks = 0;
	bType = type;
	totalInstance++;
	bNumber = totalInstance;
	up = false;
	down = false;
	left = false;
	right = false;
	bUsed = false;
	correction = {0,0,0,0};
}

Breach::~Breach() {}

Breach::Breach() {}

void Breach::input(const Uint8* keystate) {}

std::string Breach::getInstanceName(){
	std::ostringstream ss;
	ss << bNumber;
	return "breach-"+ss.str();
}

void Breach::init(SDL_Renderer *renderer) {
	bImg = utils::loadTexture(renderer, "res/breaches.png");
	
	switch(bType){
		case 'n':
			bImgRect.x = 0;
			bImgRect.y = 0;
			bImgRect.w = 8;
			bImgRect.h = 32;
			break;
		case 'e':
			bImgRect.x = 48;
			bImgRect.y = 0;
			bImgRect.w = 32;
			bImgRect.h = 8;
			break;
		case 's':
			bImgRect.x = 40;
			bImgRect.y = 0;
			bImgRect.w = 8;
			bImgRect.h = 32;
			break;
		case 'w':
			bImgRect.x = 8;
			bImgRect.y = 0;
			bImgRect.w = 32;
			bImgRect.h = 8;
			break;
	}
}
		
void Breach::update(std::unordered_map<std::string, Object*> &objectList, std::vector<std::vector<Tile*>> &grid, Uint32 ticks){
	updatePosition();
	if (totalInstance - bNumber > 3) bUsed = true;
}

SDL_Renderer* Breach::draw(SDL_Renderer *renderer, SDL_Rect cam) {
	if (cam.x >= -2 && cam.x <= 2 && cam.y >= -2 && cam.y <= 2 && cam.w == 0 && cam.h == 0) {
		correction = cam;
	} else {
		SDL_Rect* drawDest = new SDL_Rect;
		*drawDest = bDrawBox;
		SDL_RenderCopy(renderer, bImg, &bImgRect, drawDest);
	}
	return renderer;
}

void Breach::updatePosition() {
	bDrawBox.x = bDrawBox.x - correction.x;
	bDrawBox.y = bDrawBox.y - correction.y;
}

void Breach::checkBreachOverlap(std::unordered_map<std::string, Object*> &objectList, std::vector<std::vector<Tile*>> &grid) {}

bool Breach::isUsed() {
	return bUsed;
}

SDL_Rect* Breach::getRect() {
    return &bRect;
}