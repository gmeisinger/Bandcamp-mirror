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
Ooze::Ooze():state{roaming}, hostility{0} {}

//Constructor from rect
Ooze::Ooze(SDL_Rect _rect, Player *p, HUD *h):player{player},state{roaming}, hostility{0} {
    rect = _rect;
    player = p;
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

void Ooze::input(const Uint8* keystate){}

void Ooze::init(SDL_Renderer* gRenderer) {
	setSpriteSheet(utils::loadTexture(gRenderer, "res/ooze.png"), 3, 1);
    addAnimation("wandering", Animation(getSheet().getRow(0)));
    setAnimation("wandering");
	
    

	//This should be removed ASAP
    lWall = {screen_w/4, screen_h/4, screen_w/12, screen_h/2};
	rWall = {screen_w/4 * 3 - screen_w/12, screen_h/4, screen_w/12, screen_h/2};
	uWall = {screen_w/4, screen_h/4, screen_w/2, screen_h/12};
	cPillar = {screen_w/2, screen_h/2 + (tile_s * 5), tile_s};
}

void Ooze::setSpriteSheet(SDL_Texture* _sheet, int _cols, int _rows) {
    sheet = SpriteSheet(_sheet);
    sheet.setClips(_cols, _rows, rect.w, rect.h);
}

//*********TO DO:
//update motion here
void Ooze::update(std::unordered_map<std::string, Object*> *objectList, Uint32 ticks) {
	
	int x_deltav = 0;
	int y_deltav = 0;
    
    //Get the position of the player before they move
    //Needed for collision detection
    int curX = rect.x;
    int curY = rect.y;
	
	bool overlap = checkOozeOverlap(objectList, ticks);
    
	if(!overlap){

		//check which direction the player is
		if (player->getY() > rect.y + rect.h)
			y_deltav += 1;
		if (player->getX() > rect.x + rect.w)
			x_deltav += 1;
		if (player->getY() + player->getHeight() < rect.y)
			y_deltav -= 1;
		if (player->getX() + player->getWidth() < rect.x)
			x_deltav -= 1;
        
        updateVelocity(x_deltav,y_deltav);
	}
    //update animation
    updateAnimation(ticks);
    //updatePosition();
    //checkBounds(screen_w, screen_h);
    //Check you haven't collided with object
    //checkCollision(curX, curY);
}

void Ooze::increaseHostility() {
	if (hostility < 10)
		hostility++;
}
void Ooze::decreaseHostility() {
	if (hostility >  0)
		hostility--;
}

SDL_Renderer* Ooze::draw(SDL_Renderer* renderer) {
    SDL_RenderCopy(renderer, sheet.getTexture(), anim->getFrame(), getRect());
   return renderer;
}

//Checks if the player overlapped with the ooze and acts accordingly
//based on pickup's method
bool Ooze::checkOozeOverlap(std::unordered_map<std::string, Object*> *objectList, Uint32 ticks) {
	SDL_Rect* pRect = player->getRect();
	bool overlap = collision::checkCol(rect, *pRect);

	if (overlap) {
		overlapTicks += ticks;
		if (overlapTicks > 1000) {
			hud->currentHealth = std::max(0, hud->currentHealth-damage);
			std::string s = "HIT: "+getInstanceName();
			std::cout << s << std::endl;
			overlapTicks = 0;
		}
	} else {
		overlapTicks = 0;
	}

	player->setEnemy(overlap);

	return overlap;
}

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

/* <<<<<<< HEAD
void Ooze::updatePosition() {
    rect.x += x_vel;
    rect.y += y_vel;
}

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

=======
>>>>>>> origin/master */
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

void Ooze::checkCollision(int curX, int curY)
{
    //Checks the collision of each object and determines where the player should stop
    //In the future, we might need to alter this function to take in an object that
    //represents what the player is colliding with. This shouldn't be too difficult

    //LEFT WALL
    if(collision::checkCol(rect, lWall))
    {
        rect.x = curX;
    }
    if(collision::checkCol(rect, lWall))
    {
        rect.y = curY;
		//If this is not included the x movement will lock when colliding with y
		rect.x += x_vel;
    }

    //RIGHT WALL
    if(collision::checkCol(rect, rWall))
    {
        rect.x = curX;
    }
    if(collision::checkCol(rect, rWall))
    {
        rect.y = curY;
		rect.x += x_vel;
    }

    //UPPER WALL
    if(collision::checkCol(rect, uWall))
    {
        rect.x = curX;
    }
    if(collision::checkCol(rect, uWall))
    {
        rect.y = curY;
		rect.x += x_vel;
    }

    //PILLAR - very difficult to implement with this style
    if(collision::checkCol(rect, cPillar))
    {
        rect.x = curX;
    }
    if(collision::checkCol(rect, cPillar))
    {
        rect.y = curY;
		rect.x += x_vel;
    } 
}
