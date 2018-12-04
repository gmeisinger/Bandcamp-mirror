/* Team Bandcamp
 * Class function: 
 * 
*/
#include "include/player.h"
#include "include/game.h"
#include "include/collision.h"
#include "include/spritesheet.h"
#include "include/projectile.h"

constexpr int MAX_SPEED = 2;
constexpr int BORDER_SIZE = 32;
constexpr int SHORTEN_DIST = 6;

SDL_Rect playerRect;
SDL_Rect hitRect;
SDL_Rect* frame;
SpriteSheet sheet;
std::unordered_map<std::string, Animation*> anims;
Animation* anim;
int x_deltav;
int y_deltav;
int x_vel;
int y_vel;
int cooldownTicks;
bool overlapEnemy;

//Constructor - takes a texture, width and height
Player::Player(SDL_Rect _rect) {
    playerRect = _rect;
    hitRect = {playerRect.x + SHORTEN_DIST/2, playerRect.y +SHORTEN_DIST, playerRect.w - SHORTEN_DIST/2, playerRect.h - SHORTEN_DIST};
    x_deltav = 0;
    y_deltav = 0;
    x_vel = 0;
    y_vel = 0;
	cooldownTicks = 0;
	up = false;
	down = false;
	left = false;
	right = false;
	space = false;
    x = false;
	projCooldown = false;
    overlapEnemy = false;
	projsType = 's';
	//std::unordered_map<std::string, Object*> projList;
    player = this;
	correction = {0,0,0,0};
}

//
Player::Player(){}

//destructor
Player::~Player() {

}

//
std::string Player::getInstanceName(){
	return "Player"; //There should only be one instance in the current room
}

/* Summary
 * Argument  
 *
*/
void Player::init(SDL_Renderer* gRenderer){
	rendererReference = gRenderer;
	
	//set up player animations
	setSpriteSheet(utils::loadTexture(gRenderer, "res/spaceman.png"), 4, 4);
	addAnimation("down", Animation(getSheet().getRow(0)));
	addAnimation("up", Animation(getSheet().getRow(1)));
	addAnimation("left", Animation(getSheet().getRow(2)));
	addAnimation("right", Animation(getSheet().getRow(3)));
	setAnimation("down");
}

/* Summary
 * Argument  
 *
*/
void Player::setSpriteSheet(SDL_Texture* _sheet, int _cols, int _rows) {
    sheet = SpriteSheet(_sheet);
    sheet.setClips(_cols, _rows, playerRect.w, playerRect.h);
}

/* Summary
 * Argument  
 *
*/
SpriteSheet Player::getSheet() {
    return sheet;
}

/* Summary
 * Argument  
 *
*/
void Player::addAnimation(std::string tag, Animation anim) {
    anims[tag] = anim;
}

/* Summary
 * Argument  
 *
*/
Animation* Player::getAnimation(std::string tag) {
    return &anims[tag];
}

/* Summary
 * Argument  
 *
*/
void Player::setAnimation(std::string tag) {
    anim = &anims[tag];
}

//returns width of Player
int Player::getWidth() {
    return playerRect.w;
}

//returns height of Player
int Player::getHeight() {
    return playerRect.h;
}

//returns x position of Player
int Player::getX() {
    return playerRect.x;
}

//returns y position of Player
int Player::getY() {
    return playerRect.y;
}

//
SDL_Rect* Player::getRect() {
    return &playerRect;
}

SDL_Rect* Player::getHitRect() {
    return &hitRect;
}

/* Summary
 * Argument  
 *
*/
void Player::updateVelocity(int _xdv, int _ydv) {
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

// 
void Player::updatePosition() {
    playerRect.x += x_vel;
    playerRect.y += y_vel;
    hitRect.x += x_vel;
    hitRect.y += y_vel;
}

/* Summary
 * Argument  
 *
*/
void Player::checkBounds(int max_width, int max_height) {
    if (playerRect.x < BORDER_SIZE)
        playerRect.x = BORDER_SIZE;
    else if (playerRect.x + playerRect.w > max_width - BORDER_SIZE)
        playerRect.x = max_width - playerRect.w - BORDER_SIZE;

    if (playerRect.y < BORDER_SIZE)
        playerRect.y = BORDER_SIZE;
    else if (playerRect.y + playerRect.h > max_height - BORDER_SIZE)
        playerRect.y = max_height - playerRect.h - BORDER_SIZE;
}

/* Summary
 * Argument  
 *
*/
void Player::updateAnimation(Uint32 ticks) {
    if(x_vel == 0 && y_vel == 0) {
        anim->reset();
        anim->stop();
    }
    else if(x_vel > 0 && std::abs(x_vel) > std::abs(y_vel)) {
        setAnimation("right");
        anim->play();
    }
    else if(x_vel < 0 && std::abs(x_vel) > std::abs(y_vel)) {
        setAnimation("left");
        anim->play();
    }
    else if(y_vel > 0 && std::abs(y_vel) > std::abs(x_vel)) {
        setAnimation("down");
        anim->play();
    }
    else if(y_vel < 0 && std::abs(y_vel) > std::abs(x_vel)) {
        setAnimation("up");
        anim->play();
    }
    anim->update(ticks);
}

void Player::update(std::unordered_map<std::string, Object*> &objectList, std::vector<std::vector<Tile*>> &grid, Uint32 ticks) {
	std::cout << "Entered Player update" << std::endl;
	int x_deltav = 0;
	int y_deltav = 0;
    
    //Get the position of the player before they move
    //Needed for collision detection
    int curX = playerRect.x;
    int curY = playerRect.y;

	if (up)
		y_deltav -= 1;
	if (left)
		x_deltav -= 1;
	if (down)
		y_deltav += 1;
	if (right)
		x_deltav += 1;
	
  if ((space || x) && !projCooldown) {
		Projectile* newProj = new Projectile(projsType, playerRect.x, playerRect.y);
		newProj->init(rendererReference);
		objectList[newProj->getInstanceName()] = newProj;
		projCooldown = true;
	} else if (projCooldown) {
		if (cooldownTicks >= 50) {
			cooldownTicks = 0;
			projCooldown = false;
		} else {
			cooldownTicks++;
		}

	}

	updateVelocity(x_deltav, y_deltav);

    //Checks if you are overlapping an enemy, slows down velocity if you are
    //checkEnemy(x_deltav, y_deltav);

    //update animation
    updateAnimation(ticks);

	// Move box
	updatePosition();

	// Check you haven't moved off the screen
	//checkBounds(screen_w, screen_h);

    //Check you haven't collided with object
    checkCollision(curX, curY, grid);
	
	std::unordered_map<std::string, Object*>::iterator it = objectList.begin();
	while(it != objectList.end()) {
		if (it->second->getInstanceName().find("proj") != -1 || it->second->getInstanceName().find("breach") != -1) {
			it->second->draw(rendererReference, correction);
		}
		it++;
	}
	std::cout << "Exiting Player update" << std::endl;
}

/* Summary
 * Argument  
 *
*/
void Player::input(const Uint8* keystate) {
	up = keystate[SDL_SCANCODE_W] || keystate[SDL_SCANCODE_UP];
	left = keystate[SDL_SCANCODE_A] || keystate[SDL_SCANCODE_LEFT];
	down = keystate[SDL_SCANCODE_S] || keystate[SDL_SCANCODE_DOWN];
	right = keystate[SDL_SCANCODE_D] || keystate[SDL_SCANCODE_RIGHT];
	space = keystate[SDL_SCANCODE_SPACE];
    x = keystate[SDL_SCANCODE_X];
	if (up) projsType = 'n';
	else if (left) projsType = 'e';
	else if (down) projsType = 's';
	else if (right) projsType = 'w';
}

/* Summary
 * Argument  
 *
*/
SDL_Renderer* Player::draw(SDL_Renderer* renderer, SDL_Rect cam) {
    SDL_Rect* dest = new SDL_Rect;
    *dest = playerRect;
    dest->x -= cam.x;
    dest->y -= cam.y;
    SDL_RenderCopy(renderer, sheet.getTexture(), anim->getFrame(), dest);
	return renderer;
}

/* Summary
 * Argument  
 *
*/
bool Player::isUsed() {
    return false;
}

/* Summary
 * Argument  
 *
*/
void Player::setEnemy(bool _overlap) {
    overlapEnemy = _overlap;
}

void Player::checkCollision(int curX, int curY, std::vector<std::vector<Tile*>> &grid)
{
	if(collision::checkColLeft(hitRect, grid, 32) || collision::checkColRight(hitRect, grid, 32)) {
		playerRect.x = curX;
        hitRect.x = curX + SHORTEN_DIST/2;
		
		correction.x = 0;
		correction.w = 1;
    }
    
    if(collision::checkColTop(hitRect, grid, 32) || collision::checkColBottom(hitRect, grid, 32)) {
        playerRect.y = curY;
        hitRect.y = curY+SHORTEN_DIST;
        playerRect.x += x_vel;
        hitRect.x += x_vel;
        y_vel = 0;
		
		correction.y = 0;
		correction.h = 1;
		
		correction.x = x_vel;
        
		if(collision::checkColLeft(hitRect, grid, 32) || collision::checkColRight(hitRect, grid, 32)) {
            x_vel = 0; 
            playerRect.x = curX;
            hitRect.x = curX + SHORTEN_DIST/2;
			
			correction.x = 0;
			correction.w = 1;
        }
    }

	if (correction.w == 1) correction.w = 0;
	else correction.x = x_vel;
	if (correction.h == 1) correction.h = 0;
	else correction.y = y_vel;
}

/* Summary
 * Argument  
 *
*/
void Player::checkEnemy(int _xdv, int _ydv){
    if(overlapEnemy){
        x_vel -= x_vel/2;
        y_vel -= y_vel/2;
    }
}
