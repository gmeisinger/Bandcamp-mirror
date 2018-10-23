#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "include/button.h"
#include "include/game.h"
#include "include/gsm.h"

//Framework for a basic object oriented button. In the future, this may be inheritable so that different types
//of buttons can be made, or more flexible parameters will be added allowing for different images and effects to be loaded

SDL_Rect rectangle = {0, 0, 0, 0}; //area of the button
char* label = nullptr; //Text to be displayed by the button
SDL_Color color = {0, 0, 0}; //Current button color
SDL_Surface * message = nullptr;
SDL_Texture * message_texture = nullptr;

//Default pressed, unpressed, and text colors
SDL_Color unpressed = {180, 180, 180};
SDL_Color pressed = {90, 90, 90};
SDL_Color text_color = {240, 240, 240};

//Text will be rendered to a surface and then blitted to the screen

int is_pressed = 0;
SDL_Rect label_rect = {0, 0, 0, 0};
const int label_offset = 15;

TTF_Font *font = nullptr;

Button::Button(char* l, SDL_Rect r) { //Constructs the button. For now, it is a simply a text label, a rectangle, and a color.
	label = l;
	
	rectangle = r;
	color = unpressed;
	
	
	
	//The text will be vertically centered on the button and slightly offset from the left side.
	label_rect.x = rectangle.x;
	label_rect.y = rectangle.y;
	
}

void Button::init(SDL_Renderer *renderer) {
	text_color = {250, 250, 250};
	std::cout << "Init Button" << std::endl;
	font = TTF_OpenFont("res/OpenSans-Regular.ttf", 32);
	if(font == NULL) std::cout << "Error loading text!" << std::endl;
	message = TTF_RenderText_Solid(font, label, text_color);
	message_texture = SDL_CreateTextureFromSurface(renderer, message);
	if(message_texture == NULL) {
		std::cout << "Failed to create button texture." << std::endl;
	}
	label_rect.w = message->w;
	label_rect.h = message->h;
	std::cout <<"Width: " << label_rect.w << " Height: " << label_rect.h << std::endl;
}

void Button::press() { //Any visual or sound effects for pressing may be set up here
	color = pressed;
	is_pressed = 1;
}

void Button::unpress() { //Any visual or sound effects for releasing may be set up here
	color = unpressed;
	is_pressed = 0;
}

void Button::update(std::vector<Object*> objectList, Uint32 ticks) {
	
}

void Button::input(const Uint8* keystate) {
	
}

SDL_Renderer* Button::draw(SDL_Renderer *renderer) { //Text is rendered to texture and drawn to screen
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 0xFF);
	SDL_RenderFillRect(renderer, &rectangle);
	
	SDL_RenderCopy(renderer, message_texture, NULL, &label_rect);
	
	return renderer;
}