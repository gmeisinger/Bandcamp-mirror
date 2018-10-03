#include <SDL.h>
#include <vector>

#include "include/player.h"
#include "include/game.h"

SDL_Rect playerRect;
int x_deltav;
int y_deltav;
int x_vel;
int y_vel;

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
}

Player::Player(){}

//destructor
Player::~Player() {

}

void Player::init(SDL_Renderer* gRenderer){
	
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
    if (x_vel < -5)
        x_vel = -5;
    else if (x_vel > 5)
        x_vel = 5;

    if (y_vel < -5)
        y_vel = -5;
    else if (y_vel > 5)
        y_vel = 5;

    // Also update position
   this->updatePosition();
}

void Player::updatePosition() {
    playerRect.x += x_vel;
    playerRect.y += y_vel;
}

void Player::checkBounds(int max_width, int max_height) {
    if (playerRect.x < 0)
        playerRect.x = 0;
    else if (playerRect.x + playerRect.w > max_width)
        playerRect.x = max_width - playerRect.w;

    if (playerRect.y < 0)
        playerRect.y = 0;
    else if (playerRect.y + playerRect.h > max_height)
        playerRect.y = max_height - playerRect.h;
}

void Player::update(std::vector<Object*> objectList) {
	int x_deltav = 0;
	int y_deltav = 0;

	if (up)
		y_deltav -= 1;
	if (left)
		x_deltav -= 1;
	if (down)
		y_deltav += 1;
	if (right)
		x_deltav += 1;

	updateVelocity(x_deltav, y_deltav);

	// Move box
	updatePosition();

	// Check you haven't moved off the screen
	checkBounds(screen_w, screen_h);
}

void Player::input(const Uint8* keystate)
{
	up = keystate[SDL_SCANCODE_W];
	left = keystate[SDL_SCANCODE_A];
	down = keystate[SDL_SCANCODE_S];
	right = keystate[SDL_SCANCODE_D];
}

SDL_Renderer* Player::draw(SDL_Renderer* renderer) {
	SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0x00, 0xFF);
	SDL_RenderFillRect(renderer, &playerRect);
	
   return renderer;
}