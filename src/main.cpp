#include <string>
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL/SDL_image.h>
#include "include/sprite.h"

constexpr int SCREEN_WIDTH = 640;
constexpr int SCREEN_HEIGHT = 480;

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
    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
    if(gRenderer == nullptr)
    {
        std::cout << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }
    else
    {
        //set renderer color
        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
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

	//test sprite
	Sprite player_sprite = Sprite(loadTexture("res/retroMe.png"), 128, 128);

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

		/* The following is simplified for testing purposes and
		 * should be replaced with an update() function for loginc,
		 * and a draw() function to render*/
		//clear screen
		SDL_RenderClear(gRenderer);

		//draw sprite
		player_sprite.draw(gRenderer, 0, 0);

		//update screen
		SDL_RenderPresent(gRenderer);
	}

	//quit sdl
	close();
	return 0;
}