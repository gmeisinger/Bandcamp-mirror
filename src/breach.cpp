/* Team Bandcamp
 * Class function: 
 * 
*/

#include "include/breach.h"

constexpr int FIRED_SPEED = 6;

Uint32 bTicks;
static int totalInstance = 0;//How many instances of the object exist?

Breach::Breach(char type, SDL_Rect rect, SDL_Rect drawBox) {
	bRect = rect;
	bDrawBox = drawBox;
	switch(type){
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
	totalInstance++; //Increase instance Number
	bNumber = totalInstance;
	up = false;
	down = false;
	left = false;
	right = false;
	bUsed = false;
	xCorrect = 0;
	yCorrect = 0;
}

//Deconstructor
Breach::~Breach() {
}

Breach::Breach(){
	
}

void Breach::input(const Uint8* keystate) {
	up = keystate[SDL_SCANCODE_W];
	left = keystate[SDL_SCANCODE_A];
	down = keystate[SDL_SCANCODE_S];
	right = keystate[SDL_SCANCODE_D];
}

std::string Breach::getInstanceName(){
	std::ostringstream ss;
	ss << bNumber;
	return "breach-"+ss.str();
}

void Breach::init(SDL_Renderer *renderer) {
	//Set up the right Image to display
	//Eventually these images might be global, rather than loaded every time it's spawned.
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
	//checkBreachOverlap(objectList, grid);
}

SDL_Renderer* Breach::draw(SDL_Renderer *renderer, SDL_Rect cam) {
	//std::cout << "{" << cam.x << "," << cam.y << "," << cam.w << "," << cam.h << "}" << std::endl;
	SDL_Rect* drawDest = new SDL_Rect;
	*drawDest = bDrawBox;
	//Draw the sprite
    SDL_RenderCopy(renderer, bImg, &bImgRect, drawDest);
	return renderer;
}

void Breach::updatePosition() {
	if (up) {
		bDrawBox.y = bDrawBox.y + 2;
	}
	if (down) {
		bDrawBox.y = bDrawBox.y - 2;
	}
	if (left) {
		bDrawBox.x = bDrawBox.x + 2;
	}
	if (right) {
		bDrawBox.x = bDrawBox.x - 2;
	}
}

void Breach::checkBreachOverlap(std::unordered_map<std::string, Object*> &objectList, std::vector<std::vector<Tile*>> &grid) {
	/*
	std::unordered_map<std::string, Object*>::iterator it = objectList.begin();
	while(it != objectList.end()) {
		if(it->second->getInstanceName().find("ooze") != -1) {
			if (collision::checkCol(projRect, *(it->second->getRect()))) {
				it = objectList.erase(it);
				projUsed = true;
				break;
			}
		}
		it++;
	}
	
	if (!projUsed) {
		//Uhhhhh......
		if(collision::checkColLeft(projRect, grid, 32)) {
			//Create breach
			projUsed = true;
		} else if (collision::checkColRight(projRect, grid, 32)) {
			//Create breach
			projUsed = true;
		} else if (collision::checkColTop(projRect, grid, 32)) {
			//Create breach
			projUsed = true;
		} else if (collision::checkColBottom(projRect, grid, 32)) {
			//Create breach
			projUsed = true;
		}
	}
	*/
}

bool Breach::isUsed() {
	return bUsed;
}

SDL_Rect* Breach::getRect() {
    return &bRect;
}