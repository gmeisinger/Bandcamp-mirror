#include <SDL.h>
#include <SDL_image.h>

#include <ttf.h>
#include "include/utils.h"

Button test_button;
Menu::Menu() {
	SDL_Rect r;
	r.x = 400;
	r.y = 300;
	r.w = 400;
	r.h = 200;
	test_button = new Button("test", )
	
}

Menu::init() {
	font = TTF_OpenFont("Arial.ttf", 16);
}