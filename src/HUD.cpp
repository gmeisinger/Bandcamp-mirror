#include <vector>
#include <SDL.h>

#include "include/HUD.h"
#include "include/utils.h"

bool init_h;
std::vector<SDL_Texture*> hud;
SDL_Renderer* renderer_h;
SDL_Rect Temp;
SDL_Rect Oxygen;
int currentTemp;
int currentOxygen;

//Forward declaration

HUD::HUD()
{
    init_h = false;
}

HUD::~HUD()
{
    utils::destroyTextureVector(hud);
}

void HUD::init(SDL_Renderer* _renderer)
{
	renderer_h = _renderer;
	
	//load in the image of HUD (HUD.png)
	int imgFlags = IMG_INIT_PNG;
	int retFlags = IMG_Init(imgFlags);
	hud.push_back(utils::loadTexture(renderer_h, "Physics/HUD.png"));
	SDL_Rect Temp = {54, 54, 33, 91};
	SDL_Rect Oxygen = {109, 54, 33, 91};
	init_h = true;
}

void HUD::update(std::vector<Object*> objectList, Uint32 ticks){
		
}

void HUD::input(const Uint8* keystate){
	
}

SDL_Renderer* HUD::change_levels(SDL_Renderer* gRenderer, int oxygen_level, int temperature_level){
	//replace the rectangle in the oxygen indicator down a set amount (5 for now)
	SDL_SetRenderDrawColor(renderer_h, 0x00, 0xFF, 0xFF, 0xFF);
	switch(oxygen_level)
	{
		case 100:
			Oxygen = {109, 54, 33, 91};
			break;
		case 90:
			Oxygen = {109, 64, 33, 81};
			break;
		case 80:
			Oxygen = {109, 74, 33, 71};
			break;
		case 70:
			Oxygen = {109, 84, 33, 61};
			break;
		case 60:
			Oxygen = {109, 94, 33, 51};
			break;
		case 50:
			Oxygen = {109, 104, 33, 41};
			break;
		case 40:
			Oxygen = {109, 114, 33, 31};
			break;
		case 30:
			Oxygen = {109, 124, 33, 21};
			break;
		case 20:
			Oxygen = {109, 134, 33, 11};
			break;
		case 10:
			Oxygen = {109, 144, 33, 1};
			break;
		case 0:
			Oxygen = {109, 54, 33, 91};
			break;
	}
	SDL_RenderFillRect(renderer_h, &Oxygen);
	SDL_SetRenderDrawColor(renderer_h, 0x00, 0xFF, 0xFF, 0xFF);
	switch(temperature_level)
	{
		case 100:
			Temp = {54, 54, 33, 91};
			break;
		case 90:
			Temp = {54, 64, 33, 81};
			break;
		case 80:
			Temp = {54, 74, 33, 71};
			break;
		case 70:
			Temp = {54, 84, 33, 61};
			break;
		case 60:
			Temp = {54, 94, 33, 51};
			break;
		case 50:
			Temp = {54, 104, 33, 41};
			break;
		case 40:
			Temp = {54, 114, 33, 31};
			break;
		case 30:
			Temp = {54, 124, 33, 21};
			break;
		case 20:
			Temp = {54, 134, 33, 11};
			break;
		case 10:
			Temp = {54, 144, 33, 1};
			break;
		case 0:
			SDL_SetRenderDrawColor(renderer_h, 0xFF, 0x00, 0x00, 0xFF);
			Temp = {54, 54, 33, 91};
			break;
	}
	SDL_RenderFillRect(renderer_h, &Temp);
	return renderer_h;
}

SDL_Renderer* HUD::draw(SDL_Renderer* gRenderer){
	gRenderer = change_levels(gRenderer, currentOxygen, currentTemp);
	SDL_SetRenderDrawColor(renderer_h, 0, 0, 0, 255);
	SDL_RenderCopy(gRenderer, hud[0], NULL, NULL);
	return gRenderer;
}