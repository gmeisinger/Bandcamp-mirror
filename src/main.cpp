#include <string>
#include <iostream>
#include <vector>
#include <SDL.h>
#include <SDL_image.h>
#include "include/sprite.h"

constexpr int SCREEN_WIDTH = 800;
constexpr int SCREEN_HEIGHT = 600;

//function declarations
bool init();
void close();

//globals
SDL_Window* gWindow = nullptr;
SDL_Surface* gScreenSurface = nullptr;
SDL_Renderer* gRenderer = nullptr;

//Initializes SDL
bool init() {	
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
		return false;
	}
	//create window
	gWindow = SDL_CreateWindow("Bandcamp", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (gWindow == nullptr) {
		std::cout << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
		return  false;
	}
    //create renderer
    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(gRenderer == nullptr)
    {
        std::cout << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }
    else
    {
        //set renderer color
        SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
        //init PNG loading
        int imgFlags = IMG_INIT_PNG;
        if(!(IMG_Init(imgFlags) & imgFlags))
        {
            std::cout << "SDL_image could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
            return false;
        }
    }
	
	gScreenSurface = SDL_GetWindowSurface(gWindow);
	return true;
}

//loads image at specified path as a texture
//fname = relative path to image
SDL_Texture* loadTexture(std::string fname) {
    //the final texture
    SDL_Texture* newTexture = nullptr;
    //load the image
	SDL_Surface* startSurf = IMG_Load(fname.c_str());
	if (startSurf == nullptr) {
		std::cout << "Unable to load image " << fname << "! SDL Error: " << SDL_GetError() << std::endl;
		return nullptr;
	}
    //create texture from image
	newTexture = SDL_CreateTextureFromSurface(gRenderer, startSurf);
	if (newTexture == nullptr) {
		std::cout << "Unable to create texture!" << std::endl;
	}
    //free original surface
	SDL_FreeSurface(startSurf);

	return newTexture;
}

//free memory and quit
void close() {
	
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
    gRenderer = nullptr;
	gWindow = nullptr;

	// Quit SDL subsystems
    IMG_Quit();
	SDL_Quit();
}

//returns a vector containing credit textures
std::vector<SDL_Texture*> loadCredits()
{
	std::vector<SDL_Texture*> credits;
	//load textures

	credits.push_back(loadTexture("Group Member Icons/ChristianBrill_Icon.png"));
	credits.push_back(loadTexture("Group Member Icons/kyle_hartenstein_credit.png"));
	credits.push_back(loadTexture("Group Member Icons/Brendan valley - Icon.png"));
	credits.push_back(loadTexture("Group Member Icons/Brad_Credit_Icon.png"));
	credits.push_back(loadTexture("Group Member Icons/CS1666TylerThompsonIcon.png"));
	credits.push_back(loadTexture("Group Member Icons/GraemeRock.png"));
	credits.push_back(loadTexture("Group Member Icons/gm_credit.png"));
	credits.push_back(loadTexture("Group Member Icons/vc_credit.png"));
	credits.push_back(loadTexture("Group Member Icons/jbader_credit.png"));
//	Wating on Justin...
//	credits.push_back(loadTexture("Group Member Icons/gm_credit.png"));			

	return credits;
}

//plays each credit in vector for 3 seconds
void playCredits(std::vector<SDL_Texture*> creds)
{
	int alpha;
	int time;
	int elapsed;
	//play each credit
	for( auto i : creds)
	{
		//init alpha to 0
		SDL_SetTextureBlendMode(i, SDL_BLENDMODE_BLEND);
		alpha = SDL_ALPHA_TRANSPARENT;
		elapsed = 0;
		time = SDL_GetTicks();
		SDL_RenderClear(gRenderer);
		SDL_SetTextureAlphaMod(i, alpha);
		SDL_RenderCopy(gRenderer, i, NULL, NULL);
		SDL_RenderPresent(gRenderer);
		//fade in over 255ms
		while(alpha < SDL_ALPHA_OPAQUE)
		{
			elapsed = SDL_GetTicks() - time;
			time = SDL_GetTicks();
			alpha += elapsed;
			if(alpha > 255) alpha = 255;
			SDL_RenderClear(gRenderer);
			SDL_SetTextureAlphaMod(i, alpha);
			SDL_RenderCopy(gRenderer, i, NULL, NULL);
			SDL_RenderPresent(gRenderer);
		}
		SDL_Delay(2490);
		time = SDL_GetTicks();
		elapsed = 0;
		//fade out over 255ms
		while(alpha > SDL_ALPHA_TRANSPARENT)
		{
			elapsed = SDL_GetTicks() - time;
			time = SDL_GetTicks();
			alpha -= elapsed;
			if(alpha < 0) alpha = 0;
			SDL_RenderClear(gRenderer);
			SDL_SetTextureAlphaMod(i, alpha);
			SDL_RenderCopy(gRenderer, i, NULL, NULL);
			SDL_RenderPresent(gRenderer);
		}
	}
}

/*destroys a vector of textures
 *this exists outside of close() because we will quickly move away
 *from using globals. this could exist in a utilities.cpp for example.
 *we will discuss this kind of thing soon, so its subject to change
 */
void destroyTextureVector(std::vector<SDL_Texture*> vect)
{
	for(auto i : vect)
	{
		SDL_DestroyTexture(i);
		i = nullptr;
	}
}

int main() {
	if (!init()) {
		std::cout <<  "Failed to initialize!" << std::endl;
		close();
		return 1;
	}

	//quit flag
	bool quit = false;
	//event handler
	SDL_Event e;

	//load credit images
	std::vector<SDL_Texture*> credits = loadCredits();

	//test sprite, leaving this commented out for now
	//Sprite player_sprite = Sprite(loadTexture("res/retroMe.png"), 128, 128);

	//main loop
	while(!quit)
	{
		//handle events on queue
		while(SDL_PollEvent(&e) != 0)
		{
			//user requests quit
			if(e.type == SDL_QUIT)
			{
				quit = true;
			}
		
		}

		playCredits(credits);
		quit = true;
	}

	//quit sdl
	destroyTextureVector(credits);
	close();
	return 0;
}