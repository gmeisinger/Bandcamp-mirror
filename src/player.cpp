/* Team Bandcamp
 * Class function: 
 * 
*/
#include "include/player.h"
#include "include/game.h"
#include "include/collision.h"
#include "include/spritesheet.h"

constexpr int MAX_SPEED = 2;
constexpr int BORDER_SIZE = 32;

SDL_Rect playerRect;
SDL_Rect* frame;
SpriteSheet sheet;
std::unordered_map<std::string, Animation*> anims;
Animation* anim;
int x_deltav;
int y_deltav;
int x_vel;
int y_vel;
bool overlapEnemy;

//This should be removed ASAP
SDL_Rect lWall;
SDL_Rect rWall;
SDL_Rect uWall;
Circle cPillar;

//Constructor - takes a texture, width and height
Player::Player(SDL_Rect _rect) {
    playerRect = _rect;
    x_deltav = 0;
    y_deltav = 0;
    x_vel = 0;
    y_vel = 0;
	up = false;
	down = false;
	left = false;
	right = false;
    overlapEnemy = false;
}

Player::Player(){}

//destructor
Player::~Player() {

}

std::string Player::getInstanceName(){
	return "Player"; //There should only be one instance in the current room
}

void Player::init(SDL_Renderer* gRenderer){
	//set up player animations
	setSpriteSheet(utils::loadTexture(gRenderer, "res/spaceman.png"), 4, 4);
	addAnimation("down", Animation(getSheet().getRow(0)));
	addAnimation("up", Animation(getSheet().getRow(1)));
	addAnimation("left", Animation(getSheet().getRow(2)));
	addAnimation("right", Animation(getSheet().getRow(3)));
	setAnimation("down");

}

void Player::setSpriteSheet(SDL_Texture* _sheet, int _cols, int _rows) {
    sheet = SpriteSheet(_sheet);
    sheet.setClips(_cols, _rows, playerRect.w, playerRect.h);
}

SpriteSheet Player::getSheet() {
    return sheet;
}

void Player::addAnimation(std::string tag, Animation anim) {
    anims[tag] = anim;
}

Animation* Player::getAnimation(std::string tag) {
    return &anims[tag];
}

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

SDL_Rect* Player::getRect() {
    return &playerRect;
}

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

    // Also update position
//   this->updatePosition();
}

void Player::updatePosition() {
    playerRect.x += x_vel;
    playerRect.y += y_vel;
}

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

void Player::update(std::unordered_map<std::string, Object*> *objectList, Uint32 ticks) {
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

	updateVelocity(x_deltav, y_deltav);

    //Checks if you are overlapping an enemy, slows down velocity if you are
    checkEnemy(x_deltav, y_deltav);

    //update animation
    updateAnimation(ticks);

	// Move box
	updatePosition();

	// Check you haven't moved off the screen
	checkBounds(screen_w, screen_h);

    //Check you haven't collided with object
    checkCollision(curX, curY);
}

void Player::input(const Uint8* keystate)
{
	up = keystate[SDL_SCANCODE_W];
	left = keystate[SDL_SCANCODE_A];
	down = keystate[SDL_SCANCODE_S];
	right = keystate[SDL_SCANCODE_D];
}

SDL_Renderer* Player::draw(SDL_Renderer* renderer) {
	//SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0x00, 0xFF);
	//SDL_RenderFillRect(renderer, &playerRect);
    SDL_RenderCopy(renderer, sheet.getTexture(), anim->getFrame(), getRect());
   return renderer;
}

bool Player::isUsed() {
    return false;
}

void Player::setEnemy(bool _overlap) {
    overlapEnemy = _overlap;
}

void Player::checkCollision(int curX, int curY)
{
    //Checks the collision of each object and determines where the player should stop
    //In the future, we might need to alter this function to take in an object that
    //represents what the player is colliding with. This shouldn't be too difficult

    /*LEFT WALL
    if(collision::checkCol(playerRect, lWall))
    {
        playerRect.x = curX;
    }
    if(collision::checkCol(playerRect, lWall))
    {
        playerRect.y = curY;
		//If this is not included the x movement will lock when colliding with y
		playerRect.x += x_vel;
    }

    //RIGHT WALL
    if(collision::checkCol(playerRect, rWall))
    {
        playerRect.x = curX;
    }
    if(collision::checkCol(playerRect, rWall))
    {
        playerRect.y = curY;
		playerRect.x += x_vel;
    }

    //UPPER WALL
    if(collision::checkCol(playerRect, uWall))
    {
        playerRect.x = curX;
    }
    if(collision::checkCol(playerRect, uWall))
    {
        playerRect.y = curY;
		playerRect.x += x_vel;
    }

    //PILLAR - very difficult to implement with this style
    if(collision::checkCol(playerRect, cPillar))
    {
        playerRect.x = curX;
    }
    if(collision::checkCol(playerRect, cPillar))
    {
        playerRect.y = curY;
		playerRect.x += x_vel;
    } */
}

void Player::checkEnemy(int _xdv, int _ydv){
    if(overlapEnemy){
        x_vel -= x_vel/2;
        y_vel -= y_vel/2;
    }
}
