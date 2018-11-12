/* Team Bandcamp
 * Class function: 
 * 
*/
#include "include/fadeobj.h"

constexpr int FADE_SPEED = 2;

FadeObj::FadeObj(int _dest) {
	fadeIn = false;
	done = false;
	dest = _dest;
	fullScreen = {0,0, SCREEN_WIDTH, SCREEN_HEIGHT};
	currentTick = 0;
}

FadeObj::FadeObj() {
	fadeIn = true;
	done = false;
	dest = -1;
	fullScreen = {0,0, SCREEN_WIDTH, SCREEN_HEIGHT};
	currentTick = 0;
}

//Deconstructor
FadeObj::~FadeObj() {
}

void FadeObj::input(const Uint8* keystate){}

std::string FadeObj::getInstanceName(){
	return "FadeObj"; //There only should be one inst of this at a time.
}

void FadeObj::init(SDL_Renderer *renderer){
	if(fadeIn)
		currentFade = 255;
	else
		currentFade = 0;
}
		
void FadeObj::update(std::unordered_map<std::string, Object*> *objectList, std::vector<std::vector<int>> &grid, Uint32 ticks){
	currentTick += ticks;
	if(currentTick > FADE_SPEED){
		if(fadeIn && currentFade > 0)
			currentFade-=5;
		else if(!fadeIn && currentFade < 255)
			currentFade+=5;
		
		if((currentFade == 0 && fadeIn) || (currentFade == 255 && !fadeIn))
			done = true;
		
		currentTick = 0;
	}
}

SDL_Renderer* FadeObj::draw(SDL_Renderer *renderer, SDL_Rect cam){
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, currentFade);
	SDL_RenderFillRect(renderer, &fullScreen); //Black Background
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);
	return renderer;
}

bool FadeObj::isUsed() {
	return done;
}

bool FadeObj::isFadeIn(){
	return fadeIn;
}

int FadeObj::getDest(){
	return dest;
}