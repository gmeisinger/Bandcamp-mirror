#ifdef BANDCAMP_MENU_H_ //This framework is incomplete, so for the moment it is skipped over for compilation
#include <SDL.h>
#include <SDL_image.h>

#include <SDL_ttf.h>
#include "include/utils.h"
#include "include/button.h"
#include "include/menu.h"

//This is the basis for a repurposable object-oriented menu. The primary idea here is that each menu item (buttons, sliders, etc.)
//will be added to a data structure in this menu class, which will then manage input and detect when the items have been activated.
//Development was cut short for the week of 10/17, because of issues that need to be further discussed with the team


Button *test_button; //test button for proof of concept
TTF_Font *font = NULL;
Menu::Menu(char* label) { //Constructs a test button; in the future, this should be more flexible and adding items will happen via another method.
	int clicked = 0;
	SDL_Rect r;
	r.x = 400;
	r.y = 300;
	r.w = 400;
	r.h = 200;
	test_button = new Button(label, r);
	
}

void Menu::init() {
	font = TTF_OpenFont("Arial.ttf", 16);
}

void Menu::update() { //Blank update function for future use
	
}

void Menu::input() { //In the future, the input will probably look similar, but instead of checking against only the test_button when clicked it will
					 //iterate through all the items in the menu and see if any are activated by a mouse click.
//mouse x and mouse y
	int mx;
	int my;
	if(clicked == 1) {
		clicked = 0;
		test_button->unpress();
	}
	if(SDL_GetMouseState(&mx, &my) & SDL_BUTTON(SDL_BUTTON_LEFT)) {
		if(mx >= r.x && mx <= (r.x + r.w) && my >= r.y && my >= (r.y + r.h)) {
			clicked = 1;
			test_button->press();
		}
	}
}


SDL_Renderer* Menu::draw(SDL_Renderer *renderer, SDL_Surface *screen) { //As with input, in the future this will render every object in a list rather than just test_button
	test_button->draw(renderer, font, screen);
	return renderer;
}
#endif //BANDCAMP_MENU_H_