#include "include/ooze.h"
#include "include/player.h"

//initialize static member variables
int Ooze::totalOoze = 0;

constexpr int MAX_SPEED = 1;
constexpr int BORDER_SIZE = 32;

// Default Constructor
Ooze::Ooze():state{HANGRY}, hostility{0} {}

// Constructor
Ooze::Ooze(Room* room, Tilemap* t):
state{HANGRY},
hostility{0},
tilemap{t}
{
    target = player->getRect();
    curRoom = room;
    SDL_Rect *temp = curRoom->getRect();
    rect = {((temp->x + temp->w)/2) * tile_s, ((temp->y + temp->h)/2) * tile_s, 30, 30};
    totalOoze++; //Increase # of instances counter
	oozeNumber = totalOoze;
	int overlapTicks = 0;
    //Speed
    x_deltav = 0;
    y_deltav = 0;
    x_vel = 1;
    y_vel = 1;

    ate = 0;
    
    // Genetic statistics
    stats.health =      3 + utils::normDist_sd1();
    stats.attack =      3 + utils::normDist_sd1();
    stats.speed =       3 + utils::normDist_sd1();
    stats.health_cost = 3 + utils::normDist_sd1();
    stats.num_cost =    3 + utils::normDist_sd1();
    std::cout << "health" << stats.health << "\n";
    std::cout << "attack" << stats.attack << "\n";

    roomTiles.startTile = nullptr;
    roomTiles.endTile = nullptr;

    lastRoom = nullptr;
    initialized = false;
    intersects = curRoom->getIntersects();
    squeeze = false;
    squeezeItr = 0;

    iter = 0;
}

//Other constructor?
//Ooze::Ooze(State st, int hostil) :state{st}, hostility{hostil} {}

// Copy Constructor
Ooze::Ooze(const Ooze& other)
    :Ooze(other.curRoom, other.tilemap)
{
//    this.
}

//Destructor
Ooze::~Ooze(){};

std::string Ooze::getInstanceName(){
	std::ostringstream ss;
  ss << oozeNumber;
	return "ooze-"+ss.str();
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

//*********TO DO:
//update motion here
void Ooze::update(std::unordered_map<std::string, Object*> &objectList, std::vector<std::vector<Tile*>> &grid, Uint32 ticks) {
	//Checks to make sure our ooze isn't stuck in a wall
    //Must be declared here because we need the grid, but should only run on the
    //first update. Runs very quickly too
    if(!initialized) {
        initRoom(grid, curRoom->getRect());
        initialized = true;
    } 
    
    //Get the position of the ooze before it moves
    int x_deltav = 0;
	int y_deltav = 0;

    //Needed for collision detection
    int curX = rect.x;
    int curY = rect.y;

    int pickupX;
    int pickupY;

    //might move order of update calls
    //bool stateChange = updateState(objectList, ticks);
	bool overlap = checkOozeOverlap(objectList, ticks);
    bool los;
	if(!overlap){    
        if(iter % 5 == 0)
            target = pickTarget(objectList, grid);

        if (target) {
            //check which direction the target is 
            //Only move if we can see the player
            moveLine(grid, target);
            updatePosition();
        //updateVelocity(x_deltav,y_deltav);
        }
    }    
    //foundFood(getPickup(objectList));
    //update animation
    updateAnimation(ticks);
    //checkBounds(screen_w, screen_h, true);
    //Check you haven't collided with object
    if(!squeeze)
        checkCollision(curX, curY, grid, true);

    iter++;
    
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
    SDL_RenderCopy(renderer, sheet.getTexture(), anim->getFrame(), dest);\
   return renderer;
}


SDL_Rect* Ooze::pickTarget(std::unordered_map<std::string, Object*> &objectList, std::vector<std::vector<Tile*>> &grid) {
    switch(this->state) {
        case CLONING: {
            return nullptr;
        }
        case HANGRY: {
            std::unordered_map<std::string, Object*>::iterator it = objectList.begin();
            while(it != objectList.end()){
                if (!it->first.substr(0,6).compare("Pickup")) {
                    Pickup* temp = (Pickup*)it->second;
                    bool losPickup = drawLine(grid, temp->getRect());
                        
                    if(losPickup)
                        return temp->getRect();
                    else {
                        bool losPlayer = drawLine(grid, player->getRect());
                        if(losPlayer)
                            return player->getRect();
                        //If we don't have a line of sight with the player or pickup, check the other room
                        else {
                            moveRoom(grid);
                            state = ROOMEXIT;
                            return roomTiles.startTile;   
                        }
                    }                    
                }
                it++;
            }
        }
        case ROOMEXIT: {
            std::unordered_map<std::string, Object*>::iterator it = objectList.begin();
            while(it != objectList.end()){
                if (!it->first.substr(0,6).compare("Pickup")) {
                    Pickup* temp = (Pickup*)it->second;
                    bool losPickup = drawLine(grid, temp->getRect());
                        
                    if(losPickup) {
                        state = HANGRY;
                        return temp->getRect();
                    }  
                    else {
                        bool losPlayer = drawLine(grid, player->getRect());
                        if(losPlayer) {
                            state = HANGRY;
                            return player->getRect();
                        }
                        //If we don't have a line of sight with the player or pickup, check the other room
                        else if(drawLine(grid, roomTiles.endTile) || squeeze) {
                            state = ROOMENTER;
                            return roomTiles.endTile;
                        }
                        else {
                            if(collision::checkCol(rect, *roomTiles.startTile))
                                squeezeItr++;
                            if(squeezeItr == 15) {
                                squeeze = true;
                                squeezeItr = 0;
                            }
                            return roomTiles.startTile; 
                        }
                    }                  
                }
                it++;
            }
            return nullptr;
        }
        case ROOMENTER: {
            std::unordered_map<std::string, Object*>::iterator it = objectList.begin();
            while(it != objectList.end()){
                if (!it->first.substr(0,6).compare("Pickup")) {
                    Pickup* temp = (Pickup*)it->second;
                    bool losPickup = drawLine(grid, temp->getRect());
                        
                    if(losPickup) {
                        squeeze = false;
                        state = HANGRY;
                        return temp->getRect();
                    }  
                    else {
                        bool losPlayer = drawLine(grid, player->getRect());
                        if(losPlayer) {
                            squeeze = false;
                            state = HANGRY;
                            return player->getRect();
                        }
                        //If we don't have a line of sight with the player or pickup, check the other room
                        else if(collision::checkCol(rect, *roomTiles.endTile)) {
                            state = HANGRY;
                            squeeze = false;
                            //switchRoom();
                            return nullptr; 
                        }
                        else 
                            return roomTiles.endTile;
                    }                  
                }
                it++;
            }
            return nullptr;
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
            //std::cout << s << std::endl;
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


OozeState Ooze::getState() {
    return state;
}


bool Ooze::updateState(std::unordered_map<std::string, Object*> &objectList, Uint32 ticks) {

    if (ate > 2) {
        state = CLONING;
        RandomMap::setSpawnOoze(true);
        ate = 0;
        return true;
    } else if(state != ROOMENTER || state != ROOMEXIT){
        state = HANGRY;
        return true;
    }
    
    return false;
}

//Checks if the player overlapped with the ooze and acts accordingly
//based on pickup's method
bool Ooze::checkOozeOverlap(std::unordered_map<std::string, Object*> &objectList, Uint32 ticks) {
	SDL_Rect* pRect = player->getRect();
	bool overlap = collision::checkCol(rect, *pRect);
    if (overlap) {
		overlapTicks += ticks;
		if (overlapTicks > 25) {
			hud_g->currentHealth = std::max(0, hud_g->currentHealth-damage);
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


bool Ooze::checkCollision(int curX, int curY, std::vector<std::vector<Tile*>> &grid, bool move) {
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
    return false;       
}


//Uses Bresenham's alg to check to see if we have a line of sight with the player
//This draws the line fully but does NOT move the player at all
bool Ooze::drawLine(std::vector<std::vector<Tile*>> &grid, SDL_Rect* target) {
    int startX = rect.x;
    int startY = rect.y;
    int endX = target->x;
    int endY = target->y;
    colRect = {startX, startY, rect.w, rect.h};
    int slope = 0;
    int xDir;
    int yDir;
    bool sight = false;

    if (target->y > rect.y) 
        yDir = 1;
	if (target->x > rect.x) 
        xDir = 1;
	if (target->y < rect.y) {
        endY = target->y + target->h;
        yDir = -1;
    }
	if (target->x < rect.x) {
        endX = target->x + target->w;
        xDir = -1;
    }
        
    int deltaX = endX - startX;
    int deltaY = endY - startY;
    deltaX = abs(deltaX * 2);
    deltaY = abs(deltaY * 2);

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
            //checkBounds(screen_w, screen_h, false);
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
            //checkBounds(screen_w, screen_h, false);
            sight = checkCollision(colRect.x, colRect.y, grid, false);
            if(!sight)
                break;
        }
        return sight;
    }
}



//This version of Bresenham's moves the player in as stright a line as possible to 
//the player
void Ooze::moveLine(std::vector<std::vector<Tile*>> &grid, SDL_Rect* target) {
    int deltaX = target->x - rect.x;
    int deltaY = target->y - rect.y;
    int startX = rect.x;
    int startY = rect.y;
    int endX = target->x;
    int endY = target->y;
    int moveSlope = 0;
    int xDir = 0;
    int yDir = 0;

    deltaX = abs(deltaX * 2);
    deltaY = abs(deltaY * 2);

    if (target->y > rect.y) 
        yDir = 1;
	if (target->x > rect.x) 
        xDir = 1;
	if (target->y < rect.y) 
        yDir = -1;
	if (target->x < rect.x) 
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

//If we don't see the player or a pickup, move to the next room
void Ooze::moveRoom(std::vector<std::vector<Tile*>> &grid) {
    SDL_Rect* temp1;
    SDL_Rect* temp2;
    SDL_Rect* intersect;
    std::vector<std::vector<Tile*>> map = tilemap->getMap();
    Tile* endTile;
    Tile* tile;
    bool horWall = false;
    bool verWall = false; 
    int r = 0;
    int c = 0;
    int l = 0;
    int t = 0;
    for(int i = 0; i < intersects.size(); i++) {
        intersect = &intersects[i];
       
        if(intersect->w > intersect->h && intersect->w > 2 && !horWall) {
            //horizontal wall
            r = intersect->y;
            c = intersect->x + (intersect->w/2);
            horWall = true;
            verWall = false;
        }
        else{
            r = intersect->y + (intersect->h/2);
            c = intersect->x;
            verWall = true;
            horWall = false;
        }
        tile = map[r][c];
        temp1 = tile->getDest();
        bool los = drawLine(grid, temp1);
        std::cout << los << std::endl;
        //if(collision::checkCol(curRoom->getRectCopy(), *temp1) && lastRoom != map[r][c]) {
        if(los && lastRoom != map[r][c]) {
            roomTiles.door = temp1;
            lastRoom = tile;
            break;
        }            
    }    
    if(roomTiles.door == nullptr){
        tile = lastRoom;
        temp1 = tile->getDest();
        roomTiles.door = temp1;
        std::cout << "coo" << std::endl;
    }
    std::cout << "r " << r << " c " << c << " l " << l << " t " << t << std::endl;
    if(horWall) {
        t = c;
        if (temp1->y > rect.y) {
            l = r+2;
            r = r-1;
        }
        if (temp1->y < rect.y) {
            l = r-2;
            r = r+1;
        }
    }
    if(verWall) {
        l = r;
        if (temp1->x > rect.x) {
            t = c+2;
            c = c-1;
        }
        if (temp1->x < rect.x) {
            t = c-2;
            c = c+1;
        }
    }
    std::cout << "r " << r << " c " << c << " l " << l << " t " << t << std::endl;
    tile = map[r][c];
    endTile = map[l][t];
    temp1 = tile->getDest();
    temp2 = endTile->getDest();
    roomTiles.startTile = temp1;
    roomTiles.endTile = temp2; 
    /* delete temp1;
    delete temp2;
    delete intersect;
    delete tile;
    delete endTile; */
}

//Lets make sure our poor ooze isn't stuck in a wall
void Ooze::initRoom(std::vector<std::vector<Tile*>> &grid, SDL_Rect* t) {
    int attempts = 0;
    while((collision::checkColLeft(rect, grid, 32) 
    || collision::checkColRight(rect, grid, 32) 
    ||collision::checkColTop(rect, grid, 32) 
    || collision::checkColBottom(rect, grid, 32)) && attempts < 30) {
        std::cout << "Retry" << std::endl;
        rect.x += tile_s;
        rect.y += tile_s;
    }
}

void Ooze::switchRoom() {
    std::vector<Room*> n = curRoom->getNeighbors();

    for(int i = 0; i < n.size(); i++) {
        if(collision::checkCol(n[i]->getRectCopy(), rect)) {
            curRoom = n[i];
            roomTiles.door = nullptr;
            roomTiles.startTile = nullptr;
            roomTiles.endTile = nullptr;
            intersects = curRoom->getIntersects();
            std::cout << "END IN SWITCH" << std:: endl;
            return;
        }
    }

}
