#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
char* label = "";

SDL_Rect rectangle;
SDL_Rect surface_offset;
char* label;
SDL_Color color;
SDL_Color unpressed = {180, 180, 180};
SDL_Color pressed = {90, 90, 90};
SDL_Color text_color = {0, 0, 0. 0xFF};
SDL_Surface *message = NULL;

int label_x;
int label_y;
const int label_offset = 15;

Button::Button(char* l, SDL_Rect r) { //Constructs the button. For now, it is a simply a text label, a rectangle, and a color.
	label = l;
	
	rectangle = r;
	color = {180, 180, 180};
	
	surface_offset.x = rectangle.x + offset;
	surface_offset.y = rectangle.y + (rectangle.h / 2);
	
}

void Button::press() { //Any visual or sound effects for pressing may be set up here
	color = pressed;
}

void Button::unpress() { //Any visual or sound effects for releasing may be set up here
	color = unpressed;

Button::update(const Uint* keystate) {
	
	
}

SDL_Renderer* Button::draw(SDL_Renderer *renderer,  TTF_OpenFont font, SDL_Surface *screen) {
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 0xFF);
	SDL_RenderFillRect(renderer, &rectangle);
	
	message = TTF_RenderText_Solid(font, label, text_color);
	SDL_BlitSurface(message, NULL, message, screen);
	
}