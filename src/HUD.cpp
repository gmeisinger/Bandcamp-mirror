/* Team Bandcamp
 * Class function: Heads up display 
 * Displays important information for player 
*/

#include "include/HUD.h"
#include "include/utils.h"
#include "include/GSM.h"

// Global Variables
bool init_h;
std::vector<SDL_Texture*> hud;
SDL_Renderer* renderer_h;

// Resource displays 
SDL_Rect Temp;
SDL_Rect Oxygen;
SDL_Rect Health;
// SDL_Rect Power;

// Resource Values
int currentTemp;
int currentOxygen;
int currentHealth;
// int currentPower;

//Forward declaration
// Set up HUD 
HUD::HUD()
{
    init_h = false;
	currentTemp = 100;
	currentOxygen = 100;
	currentHealth = 90;
	// currentPower = 90;	// can add for power
    hud_g = this;
}

// Deconstructor for HUD 
HUD::~HUD()
{
    utils::destroyTextureVector(hud);
}

// Initialize HUD 
void HUD::init(SDL_Renderer* _renderer)
{
	renderer_h = _renderer;
	
	//load in the image of HUD (HUD.png)
	int imgFlags = IMG_INIT_PNG;
	int retFlags = IMG_Init(imgFlags);
	hud.push_back(utils::loadTexture(renderer_h, "res/HUD.png"));
	hud.push_back(utils::loadTexture(renderer_h, "res/dead.png"));
	SDL_Rect Temp = {54, 54, 33, 91};
	SDL_Rect Oxygen = {109, 54, 33, 91};
	SDL_Rect Health = {164, 54, 33, 91};
	// SDL_Rect Power = {219, 94, 33,91};  // add for power 
	init_h = true;
}

/* Update hud 
 * arguments 
 *
 *
*/
void HUD::update(std::unordered_map<std::string, Object*> &objectList, std::vector<std::vector<Tile*>> &grid, Uint32 ticks){
	if(currentHealth == 0) {
		GSM::currentScreen = 4;
		currentHealth = 90;
		currentTemp = 100;
		currentOxygen = 100;
	}
}

/* 
 * Keystate - which keys are pressed 
 *
*/
void HUD::input(const Uint8* keystate){
	
}

std::string HUD::getInstanceName(){
	return "HUD";
}

SDL_Renderer* HUD::change_levels(SDL_Renderer* gRenderer, int oxygen_level, int temperature_level, int health_level) {

	Oxygen = {109, std::min(144, 54+(91-(oxygen_level-9))), 33, std::max(1, oxygen_level-9)};
	switch(oxygen_level)
	{
		case 91 ... 100:
			SDL_SetRenderDrawColor(renderer_h, 0xFF, 0xFB, 0x05, 0xFF);
			break;
		case 81 ... 90:
			SDL_SetRenderDrawColor(renderer_h, 0xFF, 0xE5, 0x05, 0xFF);
			break;
		case 71 ... 80:
			SDL_SetRenderDrawColor(renderer_h, 0xFF, 0xC9, 0x05, 0xFF);
			break;
		case 61 ... 70:
			SDL_SetRenderDrawColor(renderer_h, 0xFF, 0xB8, 0x05, 0xFF);
			break;
		case 51 ... 60:
			SDL_SetRenderDrawColor(renderer_h, 0xFF, 0xA5, 0x05, 0xFF);
			break;
		case 41 ... 50:
			SDL_SetRenderDrawColor(renderer_h, 0xFF, 0x95, 0x05, 0xFF);
			break;
		case 31 ... 40:
			SDL_SetRenderDrawColor(renderer_h, 0xFF, 0x78, 0x05, 0xFF);
			break;
		case 21 ... 30:
			SDL_SetRenderDrawColor(renderer_h, 0xFF, 0x54, 0x05, 0xFF);
			break;
		case 11 ... 20:
			SDL_SetRenderDrawColor(renderer_h, 0xFF, 0x44, 0x05, 0xFF);
			break;
		case 1 ... 10:
			SDL_SetRenderDrawColor(renderer_h, 0xFF, 0x1C, 0x05, 0xFF);
			break;
		case 0:
			Oxygen = {0,0,0,0};
			break;
	}
	SDL_RenderFillRect(renderer_h, &Oxygen);
	
	Temp = {54, std::min(144, 54+(91-(temperature_level-9))), 33, std::max(1, temperature_level-9)};
	switch(temperature_level)
	{
		case 91 ... 100:
			SDL_SetRenderDrawColor(renderer_h, 0xFF, 0xFB, 0x05, 0xFF);
			break;
		case 81 ... 90:
			SDL_SetRenderDrawColor(renderer_h, 0xFF, 0xE5, 0x05, 0xFF);
			break;
		case 71 ... 80:
			SDL_SetRenderDrawColor(renderer_h, 0xFF, 0xC9, 0x05, 0xFF);
			break;
		case 61 ... 70:
			SDL_SetRenderDrawColor(renderer_h, 0xFF, 0xB8, 0x05, 0xFF);
			break;
		case 51 ... 60:
			SDL_SetRenderDrawColor(renderer_h, 0xFF, 0xA5, 0x05, 0xFF);
			break;
		case 41 ... 50:
			SDL_SetRenderDrawColor(renderer_h, 0xFF, 0x95, 0x05, 0xFF);
			break;
		case 31 ... 40:
			SDL_SetRenderDrawColor(renderer_h, 0xFF, 0x78, 0x05, 0xFF);
			break;
		case 21 ... 30:
			SDL_SetRenderDrawColor(renderer_h, 0xFF, 0x54, 0x05, 0xFF);
			break;
		case 11 ... 20:
			SDL_SetRenderDrawColor(renderer_h, 0xFF, 0x44, 0x05, 0xFF);
			break;
		case 1 ... 10:
			SDL_SetRenderDrawColor(renderer_h, 0xFF, 0x1C, 0x05, 0xFF);
			break;
		case 0:
			Temp = {0,0,0,0};
			break;
	}
	SDL_RenderFillRect(renderer_h, &Temp);
	
	Health = {164, 54+(90- health_level), 33, health_level+1};
	switch(health_level)
	{
		case 82 ... 90:
			SDL_SetRenderDrawColor(renderer_h, 0xFF, 0xFB, 0x05, 0xFF);
			break;
		case 73 ... 81:
			SDL_SetRenderDrawColor(renderer_h, 0xFF, 0xE5, 0x05, 0xFF);
			break;
		case 64 ... 72:
			SDL_SetRenderDrawColor(renderer_h, 0xFF, 0xC9, 0x05, 0xFF);
			break;
		case 55 ... 63:
			SDL_SetRenderDrawColor(renderer_h, 0xFF, 0xB8, 0x05, 0xFF);
			break;
		case 46 ... 54:
			SDL_SetRenderDrawColor(renderer_h, 0xFF, 0xA5, 0x05, 0xFF);
			break;
		case 37 ... 45:
			SDL_SetRenderDrawColor(renderer_h, 0xFF, 0x95, 0x05, 0xFF);
			break;
		case 28 ... 36:
			SDL_SetRenderDrawColor(renderer_h, 0xFF, 0x78, 0x05, 0xFF);
			break;
		case 19 ... 27:
			SDL_SetRenderDrawColor(renderer_h, 0xFF, 0x54, 0x05, 0xFF);
			break;
		case 10 ... 18:
			SDL_SetRenderDrawColor(renderer_h, 0xFF, 0x44, 0x05, 0xFF);
			break;
		case 1 ... 9:
			SDL_SetRenderDrawColor(renderer_h, 0xFF, 0x1C, 0x05, 0xFF);
			break;
		case 0:
			Health = {0,0,0,0};
			break;
	}
	SDL_RenderFillRect(renderer_h, &Health);

	// Can add for power
	// Power = {219, 54+(90- power_level), 33, power_level+1};
	// switch(power_level)
	// {
	// 	case 82 ... 90:
	// 		SDL_SetRenderDrawColor(renderer_h, 0xFF, 0xFB, 0x05, 0xFF);
	// 		break;
	// 	case 73 ... 81:
	// 		SDL_SetRenderDrawColor(renderer_h, 0xFF, 0xE5, 0x05, 0xFF);
	// 		break;
	// 	case 64 ... 72:
	// 		SDL_SetRenderDrawColor(renderer_h, 0xFF, 0xC9, 0x05, 0xFF);
	// 		break;
	// 	case 55 ... 63:
	// 		SDL_SetRenderDrawColor(renderer_h, 0xFF, 0xB8, 0x05, 0xFF);
	// 		break;
	// 	case 46 ... 54:
	// 		SDL_SetRenderDrawColor(renderer_h, 0xFF, 0xA5, 0x05, 0xFF);
	// 		break;
	// 	case 37 ... 45:
	// 		SDL_SetRenderDrawColor(renderer_h, 0xFF, 0x95, 0x05, 0xFF);
	// 		break;
	// 	case 28 ... 36:
	// 		SDL_SetRenderDrawColor(renderer_h, 0xFF, 0x78, 0x05, 0xFF);
	// 		break;
	// 	case 19 ... 27:
	// 		SDL_SetRenderDrawColor(renderer_h, 0xFF, 0x54, 0x05, 0xFF);
	// 		break;
	// 	case 10 ... 18:
	// 		SDL_SetRenderDrawColor(renderer_h, 0xFF, 0x44, 0x05, 0xFF);
	// 		break;
	// 	case 0 ... 9:
	// 		SDL_SetRenderDrawColor(renderer_h, 0xFF, 0x1C, 0x05, 0xFF);
	// 		break;
	// }
	// SDL_RenderFillRect(renderer_h, &Power);

	return renderer_h;
}

// Draw 
SDL_Renderer* HUD::draw(SDL_Renderer* gRenderer, SDL_Rect cam){
	gRenderer = change_levels(gRenderer, currentOxygen, currentTemp, currentHealth); // , currentPower can add for power level
	SDL_SetRenderDrawColor(renderer_h, 0, 0, 0, 255);
	SDL_RenderCopy(gRenderer, hud[0], NULL, NULL);
	if (currentHealth == 0) SDL_RenderCopy(gRenderer, hud[1], NULL, NULL);
	return gRenderer;
}

bool HUD::isUsed() {
	return false;
}

SDL_Rect* HUD::getRect(){return NULL;}
