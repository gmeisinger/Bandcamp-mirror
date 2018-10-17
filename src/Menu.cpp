#include <SDL.h>
#include <SDL_image.h>

#include <ttf.h>
#include "include/utils.h"

Button test_button;
Menu::Menu() 
	int clicked = 0;
	SDL_Rect r;
	r.x = 400;
	r.y = 300;
	r.w = 400;
	r.h = 200;
	test_button = new Button("test", r);
	
}

Menu::init() {
	font = TTF_OpenFont("Arial.ttf", 16);
}

Menu::update() {
	
}

Menu::input() {
	int mx;
	int my;
	if(clicked == 1) {
		clicked = 0;
		test_button.unpress();
	}
	if(SDL_GetMouseState(&mx, &my) & SDL_BUTTON(SDL_BUTTON_LEFT)) {
		if(mx >= r.x && mx <= (r.x + r.w) && my >= r.y && my >= (r.y + r.h)) {
			clicked = 1;
			test_button.press()
		}
	}
}

Menu::draw(SDL_Renderer *renderer, SDL_Surface *screen) {
	test_button.draw(renderer, screen);
}