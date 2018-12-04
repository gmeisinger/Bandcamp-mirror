#include "include/death.h"

constexpr int FX = 0;
constexpr int FY = 0;
constexpr int FW = 28;
constexpr int FH = 37;

Death::Death() : Screen() {

}

void Death::init(SDL_Renderer* renderer) {
	ss = SpriteSheet(utils::loadTexture(renderer, "res/samusfarnan.png"));
	ss.setClips(15, 1, 28, 37);

	anim = Animation(ss.getRow(0), false);
	anim.setFrameLength(150);
	anim.play();

	fRect = {FX, FY, FW, FH};

	alpha = 0;

	//start = true;
}

void Death::input(const Uint8* keystate) {}

void Death::update(Uint32 ticks) {
	if(anim.playedOnce) {
		SDL_Delay(500);
		GSM::currentScreen = 0;
	}
	else {
		anim.update(ticks);
	}
}

SDL_Renderer* Death::draw(SDL_Renderer* renderer) {

	SDL_RenderCopy(renderer, ss.getTexture(), anim.getFrame(), &fRect);
	//SDL_RenderFillRect(renderer, fRect);
}