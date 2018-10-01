#include "include/game.h"

constexpr int SCREEN_WIDTH = 800;
constexpr int SCREEN_HEIGHT = 600;

//Constructor
//starts new game
Game::Game()
{
	gWindow = nullptr;
	gScreenSurface = nullptr;
	gRenderer = nullptr;
	running = false;
}

//Initializes SDL
bool Game::init() {	
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
	running = true;
	return true;
}

void Game::update()
{
	//
}

void Game::draw()
{
	SDL_RenderClear(gRenderer);
	//SDL_RenderCopy();
	SDL_RenderPresent(gRenderer);
}

//main game loop
void Game::run()
{
	//event handler
	SDL_Event e;
	//credits
	Credits creds = Credits(gRenderer);
	creds.load();

	//main loop
	while(running)
	{
		//handle events on queue
		while(SDL_PollEvent(&e) != 0)
		{
			//user requests quit
			if(e.type == SDL_QUIT)
			{
				running = false;
			}
		
		}
		update();
		draw();
	}
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