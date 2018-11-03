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

//Constructor
//X and Y are in terms of the TILE MAP
Door::Door(int x, int y) {
	x_pos = x;
	y_pos = y;
	doorRect = {x*GSM::tile_s, y*GSM::tile_s,, GSM::tile_s, GSM::tile_s};
	totalInstance++; //Increase instance Number
	instanceNumber = totalInstance;
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
	setSpriteSheet(utils::loadTexture(gRenderer, "res/door.png"), 2, 7);
	addAnimation("closed", Animation(sheet.get(0,0)));
	addAnimation("closing", Animation(sheet.getRow(0)));
	addAnimation("open", Animation(sheet.get(0,6)));
	addAnimation("opening", Animation(sheet.getRow(1)));
	if(state == 0)
		setAnimation("closed");
	else
		setAnimation("open");
}

void Door::setSpriteSheet(SDL_Texture* _sheet, int _cols, int _rows) {
    sheet = SpriteSheet(_sheet);
    sheet.setClips(_cols, _rows, 32, 32);
}

void Door::update(std::unordered_map<std::string, Object*> *objectList, std::vector<std::vector<int>> grid, Uint32 ticks){
	switch(state)
	{
		case 0: //Closed
			if(toggleButton == 1 && checkCanToggle(object["Player"]))
			{
				setAnimation("opening");
				state = 1; //Sliding
				grid[y_pos][x_pos] = 2; //Set that to Ground
			}
		break;
		
		case 1: //Sliding Open
			//if(animationDone()){
			//  setAnimation("open")
			//	state = 3;
			//}
		break;
		
		case 2: //Sliding Closed
			//if(animationDone()){
			//  setAnimation("closed")
			//	state = 0;
			//}
		break;
		
		case 1: //Open
			if(toggleButton == 1 && checkCanToggle(object["Player"]))
			{
				setAnimation("closing");
				state = 2; //Sliding
				grid[y_pos][x_pos] = 2; //Set that to Wall
			}
		break;
		
		//grid. 
	}
}

bool Door::checkCanToggle(Object playerObj)
{
	Player* player = dynamic_cast<Player*>(playerObj);
	
	//Also check direction of the player later
	
	if(!directionLR && (player.y <= doorRect.y+GSM::tile_s && player.y >= doorRect.y-GSM::tile_s) && player.x <= doorRect.x+GSM::tile_s)
		return true;
	else if(directionLR && (player.x <= doorRect.x+GSM::tile_s && player.x >= doorRect.x-GSM::tile_s) && player.y <= doorRect.y+GSM::tile_s)
		return true;

	return false;
}

SDL_Renderer* Door::draw(SDL_Renderer *renderer, SDL_Rect cam){
	SDL_Rect* dest = new SDL_Rect;
    *dest = doorRect;
    dest->x -= cam.x;
    dest->y -= cam.y;
    SDL_RenderCopy(renderer, sheet.getTexture(), anim->getFrame(), dest);
	return renderer;
}