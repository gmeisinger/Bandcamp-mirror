#include <SDL.h>
#include <SDL_image.h>

#include <SDL_ttf.h>
#include "include/utils.h"
#include "include/button.h"
#include "include/menu.h"
#include "include/game.h"
#include "include/gsm.h"

//This is the basis for a repurposable object-oriented menu. The primary idea here is that each menu item (buttons, sliders, etc.)
//will be added to a data structure in this menu class, which will then manage input and detect when the items have been activated.
//Development was cut short for the week of 10/17, because of issues that need to be further discussed with the team


Button *test_button = nullptr; //test button for proof of concept
SDL_Rect menu_rect = {0, 0, 0, 0};

Menu::Menu() { //Constructs a test button; in the future, this should be more flexible and adding items will happen via another method.
	roomReference = &GSM::currentScreen;
	
}

void Menu::init(SDL_Renderer* renderer) {
	std::cout << "Init Menu" << std::endl;
	int clicked = 0;
	r.x = 400;
	r.y = 300;
	r.w = 200;
	r.h = 100;
	menu_rect.x = 40;
	menu_rect.y = 40;
	menu_rect.w = screen_w - 80;
	menu_rect.h = screen_h - 80;
	test_button = new Button("Start", r);
	test_button->init(renderer);
	std::cout << "Init menu done" << std::endl;
}

void Menu::update(Uint32 ticks) { //Blank update function for future use
	
}

void Menu::input(const Uint8* keystate) { //In the future, the input will probably look similar, but instead of checking against only the test_button when clicked it will
					 //iterate through all the items in the menu and see if any are activated by a mouse click.
//mouse x and mouse y
	int mx;
	int my;
	if(clicked == 1) {
		clicked = 0;
		test_button->unpress();
	}
	if(SDL_GetMouseState(&mx, &my) & SDL_BUTTON(SDL_BUTTON_LEFT)) {
		std::cout << "Clicked mouse; x: " << mx << ", y: " << my << std::endl;
		std::cout << "Rectangle: x: " << r.x << ", y: " << r.y << ", x2: " << r.x + r.w << ", y2: " << r.y + r.h << std::endl;
		if(mx >= r.x && mx <= (r.x + r.w) && my >= r.y && my >= (r.y + r.h)) {
			std::cout << "Clicked button" << std::endl;
			clicked = 1;
			test_button->press();
			GSM::currentScreen = 1;
		}
	}
}


SDL_Renderer* Menu::draw(SDL_Renderer *renderer) { //As with input, in the future this will render every object in a list rather than just test_button

	SDL_SetRenderDrawColor(renderer, 40, 40, 40, 0xFF);
	SDL_RenderFillRect(renderer, &menu_rect);
	test_button->draw(renderer);
	return renderer;
}