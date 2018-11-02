#ifndef BANDCAMP_MENU_H_
#define BANDCAMP_MENU_H_

#include <SDL.h>
#include <SDL_image.h>

#include "screen.h"
#include <SDL_ttf.h>
#include "utils.h"

#ifdef BANDCAMP_GSM_H_
#include "gsm.h"
#endif

#include "button.h"

class Menu : public Screen
{
	private:
		Button * test_button;
		int clicked;
		int *roomReference;
		SDL_Rect r;
		
	public:
		Menu();
		void init(SDL_Renderer* renderer);
		void input(const Uint8* keystate);
		void update(Uint32 ticks);
		SDL_Renderer* draw(SDL_Renderer * renderer);
};

#endif // BANDCAMP_MENU_H_