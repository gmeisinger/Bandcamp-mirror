/* Team Bandcamp
 * Class function: 
 * 
*/
#include "include/pickup.h"
/* =======
#include "include/physics.h"
#include "include/pickup.h"
#include "include/player.h"
#include "include/HUD.h"
#include "include/utils.h"
#include "include/testroom.h"
#include "include/ooze.h"
>>>>>>> 188008194d1ee41687ffa1b8c7571a5a951c9216 */

constexpr int HOVER_SPEED = 150;

SDL_Rect pickupRect; //The Collision Box
char pickupType;
int pickupValue;
//Image Stuff
SDL_Texture* powerUpImg;
SDL_Texture* dropShadow;
SDL_Rect currentClip, shadowClip;
SDL_Rect drawBox, shadowBox;	//Where the Image is drawn on screen
Uint32 fTicks;
int incrementY;		//How much the Image is displaced from the original spot.
static int totalInstance = 0;//How many instances of the object exist?
int instanceNumber = 0;
bool used;

//Constructor - takes a texture, width, height, pickup type, pickup value and player
Pickup::Pickup(SDL_Rect _rect, char type, int value, Player *player, HUD *h) {
    pickupRect = _rect;
	drawBox = _rect;
	shadowBox = _rect;
	incrementY = 0;
	up = true;
	fTicks = 0;
	pickupType = type;
	pickupValue = value;
	pickupPlayer = player;
	hud = h;
	totalInstance++; //Increase instance Number
	instanceNumber = totalInstance;
	
	std::string s = "SPAWNED: "+getInstanceName();
	std::cout << s << std::endl;
	used = false;
}

//Deconstructor
Pickup::~Pickup() {
}

Pickup::Pickup(){
	
}

void Pickup::input(const Uint8* keystate){}

std::string Pickup::getInstanceName(){
  std::ostringstream ss;
  ss << instanceNumber;
	return "Pickup-"+ss.str();
}

void Pickup::init(SDL_Renderer *renderer){
	//Set up the right Image to display
	
	//Eventually these images might be global, rather than loaded every time it's spawned.
	powerUpImg = utils::loadTexture(renderer, "res/powerups.png");
	dropShadow = utils::loadTexture(renderer, "res/drop shadow.png");
    currentClip.w = 32;
	currentClip.h = 32;
	currentClip.y = 0;
	
	shadowBox.y += 36;
	shadowBox.w = 32;
	shadowBox.h = 7;
	
	shadowClip.x = 0;
	shadowClip.y = 0;
	shadowClip.w = 32;
	shadowClip.h = 7;
	
	switch(pickupType){
		//Tempurature
		case 'e':
			currentClip.x = 64;
		break;
		
		//Oxygen
		case 'o':
			currentClip.x = 128;
		break;
	}
}
		
void Pickup::update(std::unordered_map<std::string, Object*> *objectList, std::vector<std::vector<int>> grid, Uint32 ticks){
	updatePosition(ticks);
	checkPickupOverlap(objectList);
	if(used)
		TestRoom::setSpawnPickup(true);
}

SDL_Renderer* Pickup::draw(SDL_Renderer *renderer, SDL_Rect cam){
	//SDL_SetRenderDrawColor(renderer, 0x00, 0x30, 0x25, 0xFF);
	//SDL_RenderFillRect(renderer, &pickupRect);
	//get dest rect from camera
	SDL_Rect* shadowDest = new SDL_Rect;
	*shadowDest = shadowBox;
	SDL_Rect* drawDest = new SDL_Rect;
	*drawDest = drawBox;
	shadowDest->x -= cam.x;
	shadowDest->y -= cam.y;
	drawDest->x -= cam.x;
	drawDest->y -= cam.y;
	//Draw the shadow and sprite
	SDL_RenderCopy(renderer, dropShadow, &shadowClip, shadowDest);
    SDL_RenderCopy(renderer, powerUpImg, &currentClip, drawDest);	
	return renderer;
}

void Pickup::updatePosition(Uint32 ticks){
	fTicks += ticks;
	if(fTicks > HOVER_SPEED) {
		
		//Change direction
		if(incrementY == 2)
			up = false;
		else if (incrementY == 0)
			up = true;
		
		//Change position of the Image (Not the hitbox)
		if(up)
			incrementY++;
		else
			incrementY--;
		
		drawBox.y = pickupRect.y + incrementY;
		shadowClip.x = 32*incrementY; 
		
		fTicks = 0;
	}
}

//Checks if the player overlapped with the pickup and acts accordingly
void Pickup::checkPickupOverlap(std::unordered_map<std::string, Object*> *objectList) {
	bool overlap = pickupPlayer->getX() < pickupRect.x + pickupRect.w &&
				   pickupPlayer->getX() + pickupPlayer->getWidth() > pickupRect.x &&
				   pickupPlayer->getY() < pickupRect.y + pickupRect.h &&
				   pickupPlayer->getY() + pickupPlayer->getHeight() > pickupRect.y;

	if (overlap){//(xOverlap && yOverlap) {
		if (pickupType == 'e') {
			hud->currentTemp = std::min(100, hud->currentTemp+pickupValue);
			//std::cout << "TEMP UP!" << std::endl;
		} else if (pickupType == 'o') {
			hud->currentOxygen = std::min(100, hud->currentOxygen+pickupValue);
			//std::cout << "O2 UP!" << std::endl;
		} else {
			//left just in case we want some other types of pickups later
		}
		
		//This only works because there is only one instance of this object. We will eventually have to 
		//make an ID system to Identify specific objects.
		//GOAL
		used = true;
		//objectList->erase(getInstanceName());
		//delete this;
	} else {
		// Check for collisions with any ooze. Calling foundFood also updates the ooze
		std::unordered_map<std::string, Object*>::iterator it = objectList->begin();
    	while(it != objectList->end()){
	        if (!it->first.substr(0,4).compare("ooze")) {
	        	Ooze* temp = (Ooze*)it->second;
	            if (temp->foundFood(this)) {
	            	used = true;
	            }
	        }
        	it++;
    	}
	}
}

bool Pickup::isUsed() {
	return used;
}

SDL_Rect* Pickup::getRect() {
    return &pickupRect;
}