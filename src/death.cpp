#include "include/death.h"
#include "include/GSM.h"

constexpr int FW = 4 * 28;
constexpr int FH = 4 * 37;
//constexpr int SCREEN_WIDTH = 800;
//constexpr int SCREEN_HEIGHT = 600;

Death::Death() : Screen() {

}

void Death::init(SDL_Renderer* renderer) {
	SDL_Texture* tex = utils::loadTexture(renderer, "res/samusfarnan.png");
	SDL_SetTextureBlendMode(tex, SDL_BLENDMODE_BLEND);
	ss = SpriteSheet(tex);
	ss.setClips(15, 1, 28, 37);

	anim = Animation(ss.getRow(0), false);
	anim.setFrameLength(100);
	anim.play();

	fRect = {SCREEN_WIDTH/2 - FW/2, SCREEN_HEIGHT/2 - FH/2, FW, FH};

	alpha = 255;
	elapsed = 0;

	//start = true;
}

void Death::input(const Uint8* keystate) {}

void Death::update(Uint32 ticks) {
	alpha--;
	SDL_SetTextureAlphaMod(ss.getTexture(), alpha);
	if(anim.playedOnce) {
		if(alpha == 0) {
			
			GSM::currentScreen = 0;
		}
	}
	else {
		anim.update(ticks);
	}
}

SDL_Renderer* Death::draw(SDL_Renderer* renderer) {
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderCopy(renderer, ss.getTexture(), anim.getFrame(), &fRect);
	//SDL_RenderFillRect(renderer, fRect);

	return renderer;
}