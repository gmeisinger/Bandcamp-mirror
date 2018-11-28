#include <SDL.h>
#include <SDL_image.h>

#include <SDL_ttf.h>
#include "include/utils.h"
#include "include/button.h"
#include "include/menu.h"
#include "include/game.h"
#include "include/GSM.h"

//This is the basis for a repurposable object-oriented menu. The primary idea here is that each menu item (buttons, sliders, etc.)
//will be added to a data structure in this menu class, which will then manage input and detect when the items have been activated.


Button *test_button = nullptr; //test button for proof of concept
SDL_Rect dummy_cam = {0, 0, 0, 0};
SDL_Rect menu_rect = {0, 0, 0, 0};
std::unordered_map<std::string, Object*> * object_list;


/* Summary
 * Argument  
 *
*/
Menu::Menu() { //Constructs a test button; in the future, this should be more flexible and adding items will happen via another method.
	roomReference = &GSM::currentScreen;
}

/* Summary
 * Argument  
 *
*/
void Menu::init(SDL_Renderer* renderer) {
	int clicked = 0; //Flag value for 
	r.x = 300;
	r.y = 250;
	r.w = 200;
	r.h = 100;
	menu_rect.x = 40;
	menu_rect.y = 40;
	menu_rect.w = SCREEN_WIDTH - 80;
	menu_rect.h = SCREEN_HEIGHT - 80;
	test_button = new Button("Start", r);
	test_button->init(renderer);
}

/* Summary
 * Argument  
 *
*/
void Menu::update(Uint32 ticks) { //If the button was clicked, we need to change the game screen!
	if(clicked == 2) GSM::currentScreen = 1;
	
	//test_button->update(object_list, ticks);
}

/* Summary
 * Argument  
 *
*/
void Menu::input(const Uint8* keystate) { //In the future, the input will probably look similar, but instead of checking against only the test_button when clicked it will
					 //iterate through all the items in the menu and see if any are activated by a mouse click.
//mouse x and mouse y
	int mx;
	int my;
	
	if(SDL_GetMouseState(&mx, &my) & SDL_BUTTON(SDL_BUTTON_LEFT)) {
		if(mx >= r.x && mx <= (r.x + r.w) && my >= r.y && my <= (r.y + r.h) && clicked != 1) { //This compares the mouse location with the rectangle of the button. If the button is clicked, the flag is set
			clicked = 1;
			test_button->press();
		}
	}
	
	else if(clicked == 1) {
		if(mx >= r.x && mx <= (r.x + r.w) && my >= r.y && my <= (r.y + r.h)) { //This compares the mouse location with the rectangle of the button. If the button is clicked, the flag is set
			clicked = 2;
		}
		else {
			clicked = 0;
			test_button->unpress();
		}
	}
	
	
}

/* Summary
 * Argument  
 *
*/
SDL_Renderer* Menu::draw(SDL_Renderer *renderer) { //As with input, in the future this will render every object in a list rather than just test_button

	SDL_SetRenderDrawColor(renderer, 40, 40, 40, 0xFF);
	SDL_RenderFillRect(renderer, &menu_rect);
	test_button->draw(renderer, dummy_cam);
	return renderer;
}