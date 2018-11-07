/* Team Bandcamp
 * Class function: 
 * 
*/

#include "include/animation.h"

constexpr int FRAME_LENGTH = 100;

std::vector< SDL_Rect > frames;
int curFrame;
Uint32 frameTicks;
bool playing;

Animation::Animation(std::vector<SDL_Rect> _frames) {
	frames = _frames;
	curFrame = 0;
	frameTicks = 0;
	playing = false;
}

// add description
Animation::Animation() {}

// add description
Animation::~Animation() {}

// add description
void Animation::play() {
	playing = true;
}

// add description
void Animation::stop() {
	playing = false;
}

// add description
void Animation::reset() {
	curFrame = 0;
	frameTicks = 0;
}

//updates animation
//	takes ticks since last updated
void Animation::update(Uint32 ticks) {
	frameTicks += ticks;
	if(playing && frameTicks > FRAME_LENGTH) {
		curFrame = (curFrame + 1) % frames.size();
		frameTicks = 0;
	}
}

// add description
SDL_Rect* Animation::getFrame() {
	return &frames[curFrame];
}

// add description
void Animation::setFrame(int _frame) {
	curFrame = _frame;
}