/* Team Bandcamp
 * Class function: 
 * 
*/

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "include/button.h"
#include "include/game.h"
#include "include/GSM.h"

//Framework for a basic object oriented button. In the future, this may be inheritable so that different types
//of buttons can be made, or more flexible parameters will be added allowing for different images and effects to be loaded

SDL_Rect rectangle = {0, 0, 0, 0}; //area of the button
char* label = nullptr; //Text to be displayed by the button
SDL_Surface * message = nullptr;
SDL_Texture * message_texture = nullptr;
int buttonNumber = 0;
//Default pressed, unpressed, and text colors
Uint8 unpressed = 150;
Uint8 pressed = 80;
SDL_Color text_color = {240, 240, 240};
int is_pressed = 0;
SDL_Rect label_rect = {0, 0, 0, 0};
const int label_offset = 15;

TTF_Font *font = nullptr;

// 
Button::Button(char* l, SDL_Rect r) { //Constructs the button. For now, it is a simply a text label, a rectangle, and a color.
	label = l;
	buttonNumber = 0;
	rectangle = r;
	
	label_rect.x = rectangle.x;
	label_rect.y = rectangle.y;	
}

// 
void Button::init(SDL_Renderer *renderer) {
	//This code writes the text to an SDL surface, then renders it to a texture.
	text_color = {250, 250, 250};
	is_pressed = 0;
	font = TTF_OpenFont("res/OpenSans-Regular.ttf", 32); //Opens a font file
	if(font == NULL) std::cout << "Error loading text!" << std::endl;
	
	message = TTF_RenderText_Solid(font, label, text_color); //Writes text to surface
	message_texture = SDL_CreateTextureFromSurface(renderer, message); //Renders the surface as a texture on video memory
	
	if(message_texture == NULL) {
		std::cout << "Failed to create button texture." << std::endl;
	}
	//The proper size of the texture is taken from the surface rendered earlier
	label_rect.w = message->w;
	label_rect.h = message->h;
	
	//The following code centers the label by finding the midpoint of the button and offsetting by the size of the label
	label_rect.x = label_rect.x + (rectangle.w / 2) - (label_rect.w / 2);
	label_rect.y = label_rect.y + (rectangle.h / 2) - (label_rect.h / 2);
}

// add description
void Button::press() { //Any visual or sound effects for pressing may be set up here
	
	is_pressed = 1;
}

// add description
void Button::unpress() { //Any visual or sound effects for releasing may be set up here
	
	is_pressed = 0;
}

void Button::update(std::unordered_map<std::string, Object*> *objectList, std::vector<std::vector<Tile*>> grid, Uint32 ticks) {}

// add description
std::string Button::getInstanceName() {
	return "Button-0";
}

// add description
bool Button::isUsed() {
	return true;
}

// add description
void Button::input(const Uint8* keystate) {
	
}

// add description
SDL_Renderer* Button::draw(SDL_Renderer *renderer, SDL_Rect cam) { //A rectangle and the texture is drawn to the screen
	Uint8 color = 0;
	if(is_pressed == 1) color = 80;
	else color = 160;
	SDL_SetRenderDrawColor(renderer, color, color, color, 255);
	SDL_RenderFillRect(renderer, &rectangle);
	
	SDL_RenderCopy(renderer, message_texture, NULL, &label_rect);
	
	return renderer;
}