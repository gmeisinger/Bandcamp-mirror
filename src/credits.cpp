#include "include/credits.h"

bool init;
std::vector<SDL_Texture*> credits;
SDL_Renderer* renderer;

Credits::Credits(SDL_Renderer* _renderer)
{
    renderer = _renderer;
    init = false;
}

Credits::~Credits()
{
    utils::destroyTextureVector(credits);
}

//returns a vector containing credit textures
void Credits::load()
{
	//load textures

	credits.push_back(utils::loadTexture(renderer, "Group Member Icons/ChristianBrill_Icon.png"));
	credits.push_back(utils::loadTexture(renderer, "Group Member Icons/kyle_hartenstein_credit.png"));
	credits.push_back(utils::loadTexture(renderer, "Group Member Icons/Brendan valley - Icon.png"));
	credits.push_back(utils::loadTexture(renderer, "Group Member Icons/Brad_Credit_Icon.png"));
	credits.push_back(utils::loadTexture(renderer, "Group Member Icons/CS1666TylerThompsonIcon.png"));
	credits.push_back(utils::loadTexture(renderer, "Group Member Icons/GraemeRock.png"));
	credits.push_back(utils::loadTexture(renderer, "Group Member Icons/gm_credit.png"));
	credits.push_back(utils::loadTexture(renderer, "Group Member Icons/vc_credit.png"));
	credits.push_back(utils::loadTexture(renderer, "Group Member Icons/jbader_credit.png"));
//	Wating on Justin...
    init = true;
}

//plays each credit in vector for 3 seconds
void Credits::play()
{
    //return if credits are not loaded, should throw an error too
    if(!init) return;
	int alpha;
	int time;
	int elapsed;
	SDL_Event skip;
	//play each credit
	for( auto i : credits)
	{
		//init alpha to 0
		SDL_SetTextureBlendMode(i, SDL_BLENDMODE_BLEND);
		alpha = SDL_ALPHA_TRANSPARENT;
		elapsed = 0;
		time = SDL_GetTicks();
		SDL_RenderClear(renderer);
		SDL_SetTextureAlphaMod(i, alpha);
		SDL_RenderCopy(renderer, i, NULL, NULL);
		SDL_RenderPresent(renderer);
		//fade in over 255ms
		while(alpha < SDL_ALPHA_OPAQUE)
		{
			elapsed = SDL_GetTicks() - time;
			time = SDL_GetTicks();
			alpha += elapsed;
			if(alpha > 255) alpha = 255;
			SDL_RenderClear(renderer);
			SDL_SetTextureAlphaMod(i, alpha);
			SDL_RenderCopy(renderer, i, NULL, NULL);
			SDL_RenderPresent(renderer);
		}
		time = SDL_GetTicks();
		elapsed = 0;
		while(elapsed < 2490)
		{
			if(SDL_PollEvent(&skip) != 0)
			{ 
				if(skip.type == SDL_QUIT)
					return;
				if(skip.type == SDL_KEYDOWN)
					break;
			}
			elapsed = SDL_GetTicks() - time;
		}
		time = SDL_GetTicks();
		//fade out over 255ms
		while(alpha > SDL_ALPHA_TRANSPARENT)
		{
			elapsed = SDL_GetTicks() - time;
			time = SDL_GetTicks();
			alpha -= elapsed;
			if(alpha < 0) alpha = 0;
			SDL_RenderClear(renderer);
			SDL_SetTextureAlphaMod(i, alpha);
			SDL_RenderCopy(renderer, i, NULL, NULL);
			SDL_RenderPresent(renderer);
		}
	}
}