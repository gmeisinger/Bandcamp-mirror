/* Team Bandcamp
 * Class function: 
 * The class that handles door operations
*/
#include "include/door.h"

/*
SpriteSheet sheet;
Animation* anim;
SDL_Texture* openImg, closedImg;
SDL_Rect doorRect; //The Collision Box
static int totalInstance = 0;//How many instances of the object exist?
int toggleButton; //What state is the "Door open button"? 0 - not pressed  1 - pressed 1st frame 2 - held
int instanceNumber = 0;
int state = 0; //State of the Door
/*
	0 - Closed
	1 - Sliding Open
	2 - Sliding Closed
	3 - Open

bool directionLR = false; //F - Up/Down T - L/R
*/

static int totalInstance = 0; //How many instances of the object exist?

//Constructor
//X and Y are in terms of the TILE MAP
Door::Door(int x, int y, bool orientation) {
	x_pos = x;
	y_pos = y;
	doorRect = {x*TILE_SIZE, y*TILE_SIZE, TILE_SIZE, TILE_SIZE};
	totalInstance++; //Increase instance Number
	instanceNumber = totalInstance;
	directionLR = orientation;
	state = 0;
}

//Deconstructor
Door::~Door() {
}

Door::Door(){}

void Door::input(const Uint8* keystate)
{
	if(keystate[SDL_SCANCODE_Z])
	{
		if(toggleButton >= 1)
			toggleButton = 2;//Held
		else
			toggleButton = 1; //First Frame Pressed
	}
	else
		toggleButton = 0;  //Not pressed
}

std::string Door::getInstanceName(){
  std::ostringstream ss;
  ss << instanceNumber;
	return "Door-"+ss.str();
}

void Door::init(SDL_Renderer* gRenderer){
	//set up Door animations
	setSpriteSheet(utils::loadTexture(gRenderer, "res/door.png"), 7, 2);
	addAnimation("closed", Animation(sheet.get(0,0)));
	addAnimation("closing", Animation(sheet.getRow(1)));
	addAnimation("open", Animation(sheet.get(0,6)));
	addAnimation("opening", Animation(sheet.getRow(0)));
	if(state == 0) 
		setAnimation("closed");
	else
		setAnimation("open");
}

void Door::setSpriteSheet(SDL_Texture* _sheet, int _cols, int _rows) {
    sheet = SpriteSheet(_sheet);
    sheet.setClips(_cols, _rows, 32, 32);	
}

void Door::update(std::unordered_map<std::string, Object*> &objectList, std::vector<std::vector<Tile*>> &grid, Uint32 ticks){
	Player * p;

	anim->update(ticks);
	
	switch(state){
		
		case 0: //Closed
		{	
			grid[y_pos][x_pos]->setBlocking(true);
			auto it = objectList.find("player");
			if (it != objectList.end())
			  p = static_cast<Player*>(it->second);
		
			if(toggleButton == 1 && checkCanToggle(p)){
				setAnimation("opening");
				anim->play();
				state = 1; //Sliding open
				 //Set that to Ground
			}
		
		}
		break;
		
		case 1: //Sliding Open
		{
			if(anim->playedOnce){
			  setAnimation("open");
			  anim->play();
				state = 3; //Open
				grid[y_pos][x_pos]->setBlocking(false);
			}
		}
		break;
		
		case 2: //Sliding Closed
		{
			if(anim->playedOnce){
				setAnimation("closed");
				anim->play();
				state = 0; //Closed
				grid[y_pos][x_pos]->setBlocking(true);
			}
		}
		break;
		
		case 3: //Open
		{
			grid[y_pos][x_pos]->setBlocking(false);
			auto it = objectList.find("player");
			if (it != objectList.end())
			p = static_cast<Player*>(it->second);
		  
			if(toggleButton == 1 && checkCanToggle(p)){
				setAnimation("closing");
				anim->play();
				state = 2; //Sliding Closed
				grid[y_pos][x_pos]->setBlocking(true); //Set that to Door
			}
			
		}
		break;
		
		//grid. 
	}
	
}

bool Door::checkCanToggle(Player*& playerObj){	
	//Also check direction of the player later
	//get the player rect
	SDL_Rect * playerRect = playerObj->getRect();
	//and check if he's close enough to the door
	//we'll just use a slightly larger rect and check for overlap
	SDL_Rect proximity = {doorRect.x - doorRect.w/2, doorRect.y - doorRect.h/2, doorRect.w * 2, doorRect.h * 2};
	if(SDL_HasIntersection(playerRect, &proximity)) {
		return true;
	}
	//if(!directionLR && (playerRect->y <= doorRect.y+TILE_SIZE && playerRect->y >= doorRect.y-TILE_SIZE*2) && (playerRect->x <= doorRect.x+TILE_SIZE && playerRect->x >= doorRect.x))
	//	return true;
	//else if(directionLR && (playerRect->x <= doorRect.x+TILE_SIZE*2 && playerRect->x >= doorRect.x-TILE_SIZE*2) && (playerRect->y >= doorRect.y-TILE_SIZE && playerRect->y <= doorRect.y))
	//	return true;

	return false;
}

void Door::addAnimation(std::string tag, Animation anim) {
    anims[tag] = anim;
}

Animation* Door::getAnimation(std::string tag) {
    return &anims[tag];
}

void Door::setAnimation(std::string tag) {
    anim = &anims[tag];
	anim->reset();
}

SDL_Renderer* Door::draw(SDL_Renderer *renderer, SDL_Rect cam){
	SDL_Rect* dest = new SDL_Rect;
    *dest = doorRect;
    dest->x -= cam.x;
    dest->y -= cam.y;
    if(directionLR) {
    	SDL_RenderCopy(renderer, sheet.getTexture(), anim->getFrame(), dest);	
    }
    else {
    	SDL_RenderCopyEx(renderer, sheet.getTexture(), anim->getFrame(), dest, 90, NULL, SDL_FLIP_NONE);
    }
    
	return renderer;
}

SDL_Rect* Door::getRect() {
	return &doorRect;
}

bool Door::isUsed(){return false;}

void Door::addRoom(Room* _room) {
	rooms.push_back(_room);
}

int Door::getState() {
	return state;
}
