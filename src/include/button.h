#ifndef BANDCAMP_BUTTON_H_
#define BANDCAMP_BUTTON_H_

#include "object.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>


class Button : public Object
{
	private:
		SDL_Rect rectangle;
		char* label;
		Uint8 unpressed;
		Uint8 pressed;
		SDL_Color text_color;
		
		int is_pressed;
		int label_x;
		int label_y;
		const int label_offset = 15;
		SDL_Surface * message;
		SDL_Texture * message_texture;

	public:
		int buttonNumber;
		Button(char * l, SDL_Rect r);
		void init(SDL_Renderer* renderer);
		void press();
		void unpress();
		void update(std::unordered_map<std::string, Object*> &objectList, std::vector<std::vector<Tile*>> &grid, Uint32 ticks);
		std::string getInstanceName();
		bool isUsed();
		void input(const Uint8* keystate);
		SDL_Renderer* draw(SDL_Renderer *renderer, SDL_Rect cam);
};

#endif // BANDCAMP_BUTTON_H_