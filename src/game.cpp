#include <SDL.h>
#include "include/game.h"
#include "include/credits.h"
#include "include/GSM.h"

constexpr int SCREEN_WIDTH = 800;
constexpr int SCREEN_HEIGHT = 600;
constexpr int TILE_SIZE = 32;

int screen_w;
int screen_h;
int tile_s;

//Starts new game
Game::Game() {
	gWindow = nullptr;
	gRenderer = nullptr;
	running = false;
	GSM gsm;
	screen_w = SCREEN_WIDTH;
	screen_h = SCREEN_HEIGHT;
	tile_s = TILE_SIZE;
}

bool Game::init() {
	
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
		return false;
	}

	if(!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
		std::cout << "Warning: Linear texture filtering not enabled!" << std::endl;
	}
	
	gWindow = SDL_CreateWindow("Bandcamp", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (gWindow == nullptr) {
		std::cout << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
		return  false;
	}

	// Adding VSync to avoid absurd framerates
	gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (gRenderer == nullptr) {	
		std::cout << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
		return  false;
	}
	//Initialize PNG loading
	int imgFlags = IMG_INIT_PNG;
	if( !( IMG_Init( imgFlags ) & imgFlags ) )
	{
		printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
		return false;
	}
	// Set renderer draw/clear color
	SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
	
	//Start the GSM
	gsm.init(gRenderer);
	
	running = true;
	return true;
}

void Game::update() {
	gsm.update();
}

void Game::draw() {
	//Clear the Screen
	SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
	SDL_RenderClear(gRenderer);
	
	//Draw the current Screen
	gRenderer = gsm.draw(gRenderer);
	SDL_RenderPresent(gRenderer);
}

void Game::input(const Uint8* keystate){
	gsm.input(keystate);
}

//main game loop
void Game::run() {
	//event handler
	SDL_Event e;
	
	//main loop
	while(running) {
		//handle events on queue
		while(SDL_PollEvent(&e) != 0) {
			//user requests quit
			if(e.type == SDL_QUIT) {
				running = false;
			}
		
		}
		
		const Uint8* keystate = SDL_GetKeyboardState( NULL );
		
		input(keystate);
		update();
		draw();
	}
	//credits
	Credits creds = Credits(gRenderer);
	creds.load();
	creds.play();
	close();
}

//free memory and quit
void Game::close() {
	
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
    gRenderer = nullptr;
	gWindow = nullptr;

	// Quit SDL subsystems
    IMG_Quit();
	SDL_Quit();
}