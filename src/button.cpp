#ifdef BANDCAMP_BUTTON_H_

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "include/button.h"

//Framework for a basic object oriented button. In the future, this may be inheritable so that different types
//of buttons can be made, or more flexible parameters will be added allowing for different images and effects to be loaded

SDL_Rect rectangle; //area of the button
SDL_Rect surface_offset; //the x and y of this rectangle determine the button's offset
char* label; //Text to be displayed by the button
SDL_Color color; //Current button color

//Default pressed, unpressed, and text colors
SDL_Color unpressed = {180, 180, 180};
SDL_Color pressed = {90, 90, 90};
SDL_Color text_color = {0, 0, 0, 0xFF};

//Text will be rendered to a surface and then blitted to the screen
SDL_Surface *message = NULL;

int is_pressed = 0;

int label_x;
int label_y;
const int label_offset = 15;

Button::Button(char* l, SDL_Rect r) { //Constructs the button. For now, it is a simply a text label, a rectangle, and a color.
	label = l;
	
	rectangle = r;
	color = unpressed;
	
	//The text will be vertically centered on the button and slightly offset from the left side.
	int label_x = rectangle.x + label_offset;
	int label_y = rectangle.y + (rectangle.h / 2);
	
}

void Button::press() { //Any visual or sound effects for pressing may be set up here
	color = pressed;
	is_pressed = 1;
}

void Button::unpress() { //Any visual or sound effects for releasing may be set up here
	color = unpressed;
	is_pressed = 0;
}

void Button::update(const Uint8* keystate) {
	
}

SDL_Renderer* Button::draw(SDL_Renderer *renderer,  TTF_Font * font, SDL_Surface *screen) { //General idea of render; currently, it draws a rectangle, renders text, and blits it to the screen.
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 0xFF);
	SDL_RenderFillRect(renderer, &rectangle);
	
	//Issue with this is that it requires the screen to be passed throughout the entire program as a surface object; this will require some restructuring
	message = TTF_RenderText_Solid(font, label, text_color);
	SDL_BlitSurface(message, NULL, screen, &surface_offset);
	
	return renderer;
}

#endif