#include "include/animation.h"

std::vector< SDL_Rect > frames;
int curFrame;
bool playing;

Animation::Animation(std::vector<SDL_Rect> _frames) {
	frames = _frames;
	curFrame = 0;
	playing = false;
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
}

void Animation::update() {
	if(playing) {
		curFrame = (curFrame + 1) % frames.size();
	}
}

SDL_Rect* Animation::getFrame() {
	return &frames[curFrame];
}

void Animation::setFrame(int _frame) {
	curFrame = _frame;
}