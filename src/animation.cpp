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
bool loop;

Animation::Animation(std::vector<SDL_Rect> _frames) {
	frames = _frames;
	curFrame = 0;
	frameTicks = 0;
	playing = false;
	loop = true;
}

Animation::Animation(std::vector<SDL_Rect> _frames, bool _loop) {
	frames = _frames;
	curFrame = 0;
	frameTicks = 0;
	playing = false;
	loop = _loop;
}

Animation::Animation() {}

Animation::~Animation() {}

void Animation::play() {
	playing = true;
}

void Animation::stop() {
	playing = false;
}

void Animation::reset() {
	curFrame = 0;
	frameTicks = 0;
}

//updates animation
//	takes ticks since last updated
void Animation::update(Uint32 ticks) {
	frameTicks += ticks;
	if(playing && frameTicks > FRAME_LENGTH) {
		if(!loop && curFrame == (frames.size() -1)) {
			//this means if it doesnt loop then we stay on the last frame
			stop();
			break;
		}
		curFrame = (curFrame + 1) % frames.size();
		frameTicks = 0;
	}
}

SDL_Rect* Animation::getFrame() {
	return &frames[curFrame];
}

void Animation::setFrame(int _frame) {
	curFrame = _frame;
}