#include "include/HUD.h"
#include "include/utils.h"

bool init_h;
std::vector<SDL_Texture*> hud;
SDL_Renderer* renderer_h;
SDL_Rect Temp;
SDL_Rect Oxygen;

HUD::HUD(SDL_Renderer* _renderer)
{
    renderer_h = _renderer;
    init_h = false;
}

HUD::~HUD()
{
    utils::destroyTextureVector(hud);
}

void HUD::init_HUD()
{
	//load in the image of HUD (HUD.png)
	int imgFlags = IMG_INIT_PNG;
	int retFlags = IMG_Init(imgFlags);
	hud.push_back(utils::loadTexture(renderer_h, "Physics/HUD.png"));
	SDL_Rect Temp = {54, 54, 33, 91};
	SDL_Rect Oxygen = {109, 54, 33, 91};
	SDL_SetRenderDrawColor(renderer_h, 0x00, 0xFF, 0xFF, 0xFF);
	SDL_RenderFillRect(renderer_h, &Temp);
	SDL_RenderFillRect(renderer_h, &Oxygen);
	SDL_RenderCopy(renderer_h, hud[0], NULL, NULL);
	SDL_RenderPresent(renderer_h);
	init_h = true;
}

void HUD::lower_oxygen()
{
	//replace the rectangle in the oxygen indicator down a set amount (5 for now)
	if(!init_h) return;
	
}

void HUD::raise_oxygen(int resource_value)
{
	//replace the rectangle in the oxygen indicator up a set amount (passed by resource value)
	if(!init_h) return;
	
}

void HUD::lower_temperature()
{
	//replace the rectangle in the temperature indicator down a set amount (5 for now)
	if(!init_h) return;
	
}

void HUD::raise_temperature(int resource_value)
{
	//replace the rectangle in the remperature indicator down a set amount (passed by resource value)
	if(!init_h) return;
	
}
