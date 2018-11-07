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
Ooze::Ooze():state{ROAMING}, hostility{0} {}

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
Ooze::Ooze(SDL_Rect _rect, Player *player, HUD *h):player{player},state{ROAMING}, hostility{0} {
    rect = _rect;
    this->player = player;
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
	
    

}

void Ooze::setSpriteSheet(SDL_Texture* _sheet, int _cols, int _rows) {
    sheet = SpriteSheet(_sheet);
    sheet.setClips(_cols, _rows, rect.w, rect.h);
}

//*********TO DO:
//update motion here
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
    bool los;
	if(!overlap){
        //Only move if we can see the player
        los = drawLine(grid);
        std::cout << los << std::endl;
        if(los){
            moveLine(grid);
            updatePosition();
        }
  }
    /*
    
    //target = getPickup(objectList)->getRect();
	if(!overlap){

        //uncomment the line below to change the ooze to chasing the pickups
        //target = pickTarget(objectList);

		//check which direction the player is 
		if (player->getY() > rect.y + rect.h)
			y_deltav += 1;
		if (player->getX() > rect.x + rect.w)
			x_deltav += 1;
		if (player->getY() + player->getHeight() < rect.y)
			y_deltav -= 1;
		if (player->getX() + player->getWidth() < rect.x)
			x_deltav -= 1;
        
        updateVelocity(x_deltav,y_deltav);*/
    //foundFood(getPickup(objectList));
    //update animation
    updateAnimation(ticks);

    checkBounds(screen_w, screen_h, true);
    //Check you haven't collided with object
    checkCollision(curX, curY, grid, true);
  /*
    updatePosition();
    checkBounds(screen_w, screen_h);
    //Check you haven't collided with object
    checkCollision(curX, curY, grid);
    */

}

void Ooze::increaseHostility() {
	if (hostility < 10)
		hostility++;
}
void Ooze::decreaseHostility() {
	if (hostility >  0)
		hostility--;
}

SDL_Renderer* Ooze::draw(SDL_Renderer* renderer, SDL_Rect cam) {
    SDL_Rect* dest = new SDL_Rect;
    *dest = rect;
    dest->x -= cam.x;
    dest->y -= cam.y;
    SDL_RenderCopy(renderer, sheet.getTexture(), anim->getFrame(), dest);
    return renderer;
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

int Ooze::getAte() {
    return ate;
}

bool Ooze::updateState(std::unordered_map<std::string, Object*> *objectList, Uint32 ticks) {
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

void Ooze::updatePosition() {
    rect.x += x_vel;
    rect.y += y_vel;
}

void Ooze::checkBounds(int max_width, int max_height, bool move) {
    if(move)
    {
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
    else
    {
        if (colRect.x < BORDER_SIZE){
            colRect.x = BORDER_SIZE;
        }
        else if (colRect.x + colRect.w > max_width - BORDER_SIZE){
            colRect.x = max_width - colRect.w - BORDER_SIZE;
        }
        
        if (colRect.y < BORDER_SIZE){
            colRect.y = BORDER_SIZE;
        }
        else if (colRect.y + colRect.h > max_height - BORDER_SIZE){
            colRect.y = max_height - colRect.h - BORDER_SIZE;
        }
    }    
}


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

bool Ooze::checkCollision(int curX, int curY, std::vector<std::vector<int>> grid, bool move) {
    //Checks the collision of each object and determines where the ooze should stop
    //Also checks to see if ooze has line of sight
    if(move) {
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
    else {
        if(collision::checkColLeft(colRect, grid, 32) || collision::checkColRight(colRect, grid, 32)) 
            return false;
        if(collision::checkColTop(colRect, grid, 32) || collision::checkColBottom(colRect, grid, 32)) 
            return false;
        else 
            return true;
    }        
}


//Uses Bresenham's alg to check to see if we have a line of sight with the player
//This draws the line fully but does NOT move the player at all
bool Ooze::drawLine(std::vector<std::vector<int>> grid) {
    int deltaX = player->getX() - rect.x;
    int deltaY = player->getY() - rect.y;
    int startX = rect.x;
    int startY = rect.y;
    int endX = player->getX();
    int endY = player->getY();
    colRect = {startX, startY, rect.w, rect.h};
    int slope = 0;
    int xDir;
    int yDir;
    bool sight = false;

    deltaX = abs(deltaX * 2);
    deltaY = abs(deltaY * 2);

    if (player->getY() > rect.y) 
        yDir = 1;
	if (player->getX() > rect.x) 
        xDir = 1;
	if (player->getY() < rect.y) 
        yDir = -1;
	if (player->getX() < rect.x) 
        xDir = -1;
        

    if(deltaX > deltaY) {
        slope = deltaY * 2 - deltaX;
        while(startX != endX) {
            if(slope >= 0) {
                startY += yDir;
                colRect.y += yDir;
                slope -= deltaX;
            }

            startX += xDir;
            colRect.x += xDir;
            slope += deltaY;
            checkBounds(screen_w, screen_h, false);
            sight = checkCollision(colRect.x, colRect.y, grid, false);
            if(!sight)
                break;
        }
        return sight;
    }
    else {
        slope = deltaX * 2 - deltaY;
        while(startY != endY) {
            if(slope >= 0) {
                startX += xDir;
                colRect.x += xDir;
                slope -= deltaY;
            }

            startY += yDir;
            colRect.y += yDir;
            slope += deltaX;
            checkBounds(screen_w, screen_h, false);
            sight = checkCollision(colRect.x, colRect.y, grid, false);
            if(!sight)
                break;
        }
        return sight;
    }

}

//This version of Bresenham's moves the player in as stright a line as possible to 
//the player
void Ooze::moveLine(std::vector<std::vector<int>> grid) {
    int deltaX = player->getX() - rect.x;
    int deltaY = player->getY() - rect.y;
    int startX = rect.x;
    int startY = rect.y;
    int endX = player->getX();
    int endY = player->getY();
    int moveSlope = 0;
    int xDir;
    int yDir;

    deltaX = abs(deltaX * 2);
    deltaY = abs(deltaY * 2);

    if (player->getY() > rect.y) 
        yDir = 1;
	if (player->getX() > rect.x) 
        xDir = 1;
	if (player->getY() < rect.y) 
        yDir = -1;
	if (player->getX() < rect.x) 
        xDir = -1;

    if(deltaX > deltaY) {
        moveSlope = deltaY * 2 - deltaX;
        if(moveSlope >= 0) {
            startY += yDir;
            moveSlope -= deltaX;
            y_vel = yDir;
        }
        else
            y_vel = 0;

        startX += xDir;
        moveSlope += deltaY;
        x_vel = xDir;
    }
    else {
        moveSlope = deltaX * 2 - deltaY;
        if(moveSlope >= 0) {
            startX += xDir;
            moveSlope -= deltaY;
            x_vel = xDir;
        }
        else
            x_vel = 0;

        startY += yDir;
        moveSlope += deltaX;
        y_vel = yDir;
    }
}

/*currently checks collisions with room features (walls etc.)
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
}*/
