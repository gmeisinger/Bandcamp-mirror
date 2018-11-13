#include "include/ooze.h"

//SDL_Rect rect;
//SpriteSheet sheet;

//initialize static member variables
int Ooze::totalOoze = 0;


//int x_vel;
//int y_vel;

constexpr int MAX_SPEED = 1;
constexpr int BORDER_SIZE = 32;

// Default Constructor
Ooze::Ooze():state{HANGRY}, hostility{0} {}

//Constructor from rect
/* <<<<<<< HEAD
Ooze::Ooze(SDL_Rect _rect, Player *p, HUD *h):player{player},state{roaming}, hostility{0} {
    rect = _rect;
    player = p;
	hud = h;
	totalOoze++; //Increase # of instances counter
	oozeNumber = totalOoze;
	Animation* anim;
	int overlapTicks = 0;
======= */
Ooze::Ooze(SDL_Rect _rect, Player *player, HUD *h):player{player},state{HANGRY}, hostility{0} {
    rect = _rect;
    this->player = player;
    target = player->getRect();
	hud = h;
	totalOoze++; //Increase # of instances counter
	oozeNumber = totalOoze;
	Animation* anim;
	int overlapTicks = 0;
    //Speed
    x_deltav = 0;
    y_deltav = 0;
    x_vel = 1;
    y_vel = 1;

    ate = 0;
}

//Other constructor?
//Ooze::Ooze(State st, int hostil) :state{st}, hostility{hostil} {}

//Destructor
Ooze::~Ooze(){};

std::string Ooze::getInstanceName(){
	std::ostringstream ss;
  ss << oozeNumber;
	return "Ooze-"+ss.str();
}

/* Summary
 * Argument  
 *
*/
void Ooze::input(const Uint8* keystate){}

/* Summary
 * Argument  
 *
*/
void Ooze::init(SDL_Renderer* gRenderer) {
	setSpriteSheet(utils::loadTexture(gRenderer, "res/ooze.png"), 3, 1);
    addAnimation("wandering", Animation(getSheet().getRow(0)));
    setAnimation("wandering");
}

/* Summary
 * Argument  
 *
*/
void Ooze::setSpriteSheet(SDL_Texture* _sheet, int _cols, int _rows) {
    sheet = SpriteSheet(_sheet);
    sheet.setClips(_cols, _rows, rect.w, rect.h);
}

void Ooze::update(std::unordered_map<std::string, Object*> *objectList, std::vector<std::vector<int>> grid, Uint32 ticks) {
	
	int x_deltav = 0;
	int y_deltav = 0;
    
    //Get the position of the player before they move
    //Needed for collision detection
    int curX = rect.x;
    int curY = rect.y;

    int pickupX;
    int pickupY;
	
    //might move order of update calls
    bool stateChange = updateState(objectList, ticks);

	bool overlap = checkOozeOverlap(objectList, ticks);
    
    //target = getPickup(objectList)->getRect();
	if(!overlap){

        //uncomment the line below to change the ooze to chasing the pickups
        target = pickTarget(objectList);

        //check which direction the target is 
        if (target->y > rect.y)
            y_deltav += 1;
        if (target->x > rect.x)
            x_deltav += 1;
        if (target->y < rect.y)
            y_deltav -= 1;
        if (target->x < rect.x)
            x_deltav -= 1;

		
        
        updateVelocity(x_deltav,y_deltav);
	}
    //foundFood(getPickup(objectList));
    //update animation
    updateAnimation(ticks);
    updatePosition();
    checkBounds(screen_w, screen_h);
    //Check you haven't collided with object
    checkCollision(curX, curY, grid);
}

/* Summary
 * Argument  
 *
*/
void Ooze::increaseHostility() {
	if (hostility < 10)
		hostility++;
}

/* Summary
 * Argument  
 *
*/
void Ooze::decreaseHostility() {
	if (hostility >  0)
		hostility--;
}

/* Summary
 * Argument  
 *
*/
SDL_Renderer* Ooze::draw(SDL_Renderer* renderer, SDL_Rect cam) {
    SDL_Rect* dest = new SDL_Rect;
    *dest = rect;
    dest->x -= cam.x;
    dest->y -= cam.y;
    SDL_RenderCopy(renderer, sheet.getTexture(), anim->getFrame(), dest);
   return renderer;
}

SDL_Rect* Ooze::pickTarget(std::unordered_map<std::string, Object*> *objectList) {
    switch(this->state) {
        case HANGRY: {
            std::unordered_map<std::string, Object*>::iterator it = objectList->begin();
            while(it != objectList->end()){
                if (!it->first.substr(0,6).compare("Pickup")) {
                    //std::cout << "there is a pickup :) " << std::endl;
                    Pickup* temp = (Pickup*)it->second;
                    return temp->getRect();
                }
                it++;
            }
        }
        default:
            return player->getRect();
    }
}

// TODO: combine this with the overlap method below, which
//       checks for overlap betw. ooze and player
bool Ooze::foundFood(Pickup* food) {
    if (food) {
        SDL_Rect* fRect = food->getRect();
        bool overlap = collision::checkCol(rect, *fRect);
        if (overlap) {
            //food->use();
            ate = ate + 1;
            std::string s = getInstanceName() + " ATE: "+ food->getInstanceName() + ". HAS ATE: " + std::to_string(ate);
            std::cout << s << std::endl;
            return true;
        }
    }
    return false;
}

/* Summary
 * Argument  
 *
*/
int Ooze::getAte() {
    return ate;
}

/* Summary
 * Argument  
 *
*/
bool Ooze::updateState(std::unordered_map<std::string, Object*> *objectList, Uint32 ticks) {
    if (ate > 2) {
        state = ROAMING;
        return true;
    } 
    
    return false;
}

//Checks if the player overlapped with the ooze and acts accordingly
//based on pickup's method
bool Ooze::checkOozeOverlap(std::unordered_map<std::string, Object*> *objectList, Uint32 ticks) {
	SDL_Rect* pRect = player->getRect();
	bool overlap = collision::checkCol(rect, *pRect);

	if (overlap) {
		overlapTicks += ticks;
		if (overlapTicks > 25) {
			hud->currentHealth = std::max(0, hud->currentHealth-damage);
			std::string s = "HIT: "+getInstanceName();
			//std::cout << s << std::endl;
			overlapTicks = 0;
		}
	} else {
		overlapTicks = 0;
	}

	player->setEnemy(overlap);

	return overlap;
}

/* Summary
 * Argument  
 *
*/
void Ooze::updateAnimation(Uint32 ticks) {

    if(true) { //ticks/10%2 == 2
        setAnimation("wandering");
        anim->play();
        //std::cout << "ooze animating";
    }
    else {
        anim->reset();
        anim->stop();
    }
    anim->update(ticks);
}

/* Summary
 * Argument  
 *
*/
void Ooze::updatePosition() {
    rect.x += x_vel;
    rect.y += y_vel;
}

/* Summary
 * Argument  
 *
*/
void Ooze::checkBounds(int max_width, int max_height) {
    if (rect.x < BORDER_SIZE){
        rect.x = BORDER_SIZE;
        x_vel = -x_vel;
    }
    else if (rect.x + rect.w > max_width - BORDER_SIZE){
        rect.x = max_width - rect.w - BORDER_SIZE;
        x_vel = -x_vel;
    }
    
    if (rect.y < BORDER_SIZE){
        rect.y = BORDER_SIZE;
        y_vel = -y_vel;
    }
    else if (rect.y + rect.h > max_height - BORDER_SIZE){
        rect.y = max_height - rect.h - BORDER_SIZE;
        y_vel = -y_vel;
    }
}

/* Summary
 * Argument  
 *
*/
bool Ooze::isUsed() { return false; }

Animation* Ooze::getAnimation(std::string tag) { return &anims[tag]; }

void Ooze::setAnimation(std::string tag) { anim = &anims[tag]; }

void Ooze::addAnimation(std::string tag, Animation anim) { anims[tag] = anim; }

SpriteSheet Ooze::getSheet() { return sheet; }

//returns width
int Ooze::getWidth() { return rect.w; }

//returns height
int Ooze::getHeight() { return rect.h; }

//returns x position
int Ooze::getX() { return rect.x; }

//returns y position
int Ooze::getY() { return rect.y; }

SDL_Rect* Ooze::getRect() { return &rect; }

void Ooze::updateVelocity(int _xdv, int _ydv) {
    /*
    // If we dont want out dot to be in a frictionless vacuum...
    if (_xdv == 0) {
        // No user-supplied "push", return to rest
        if (x_vel > 0)
            _xdv = -1;
        else if (x_vel < 0)
            _xdv = 1;
    }
    if (_ydv == 0) {
        if (y_vel > 0)
            _ydv = -1;
        else if (y_vel < 0)
            _ydv = 1;
    }
     */
    
    // Speed up/slow down
    x_vel += _xdv;
    y_vel += _ydv;

    // Check speed limits
    if (x_vel < -1 * MAX_SPEED)
        x_vel = -1 * MAX_SPEED;
    else if (x_vel > MAX_SPEED)
        x_vel = MAX_SPEED;

    if (y_vel < -1 * MAX_SPEED)
        y_vel = -1 * MAX_SPEED;
    else if (y_vel > MAX_SPEED)
        y_vel = MAX_SPEED;
}

//currently checks collisions with room features (walls etc.)
void Ooze::checkCollision(int curX, int curY, std::vector<std::vector<int>> grid)
{
    //Checks the collision of each object and determines where the player should stop
    //In the future, we might need to alter this function to take in an object that
    //represents what the player is colliding with. This shouldn't be too difficult
    if(collision::checkColLeft(rect, grid, 32) || collision::checkColRight(rect, grid, 32)) {
        rect.x = curX;
    }
    
    if(collision::checkColTop(rect, grid, 32) || collision::checkColBottom(rect, grid, 32)) {
        rect.y = curY;

        rect.x += x_vel;

        y_vel = 0;
        if(collision::checkColLeft(rect, grid, 32) || collision::checkColRight(rect, grid, 32)) {
            x_vel = 0; 
            rect.x = curX;
        }
    }
}