/* Team Bandcamp
 * Class function: 
 * 
*/

#include "include/animation.h"

constexpr int FRAME_LENGTH = 100;

std::vector< SDL_Rect > frames;
int curFrame;
Uint32 frameTicks;
bool playing, loop;

Animation::Animation(std::vector<SDL_Rect> _frames) {
	frames = _frames;
	curFrame = 0;
	frameTicks = 0;
	playing = false;
	loop = true;
	playedOnce = false;
}

Animation::Animation(std::vector<SDL_Rect> _frames, bool _loop) {
	frames = _frames;
	curFrame = 0;
	frameTicks = 0;
	playing = false;
	loop = _loop;
	playedOnce = false;
}

//One Frame "animation"
Animation::Animation(SDL_Rect * frame) {
	frames.push_back(*frame);
	curFrame = 0;
	frameTicks = 0;
	playing = false;
	loop = false;
	playedOnce = false;
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
	playedOnce = false;
	curFrame = 0;
	frameTicks = 0;
}

//updates animation
//	takes ticks since last updated
void Animation::update(Uint32 ticks) {
	frameTicks += ticks;
	if(playing && frameTicks > FRAME_LENGTH) {
		if(curFrame == (frames.size() -1)) {
			playedOnce = true; //regardless of whether it loops or not, we can check if the animation has played once.
			
			//this means if it doesnt loop then we stay on the last frame
			if(!loop)
			{
				stop();
				return; //break;
			}
		}
		curFrame = (curFrame + 1) % frames.size();
		frameTicks = 0;
	}
}

// add description
SDL_Rect* Animation::getFrame() {
	return &frames[curFrame];
}

int Animation::getCurFrame(){
	return curFrame;
}

std::vector< SDL_Rect >* Animation::getFrames(){
	return &frames;
}

//add description
void Animation::setFrame(int _frame) {
	curFrame = _frame;
}