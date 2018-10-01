#include "include/game.h"
#include "include/sprite.h"

constexpr int SCREEN_WIDTH = 800;
constexpr int SCREEN_HEIGHT = 600;
constexpr int TILE_SIZE = 128;

//Constructor
//starts new game
Game::Game()
{
	gWindow = nullptr;
	gScreenSurface = nullptr;
	gRenderer = nullptr;
	running = false;
}

bool Game::init()
{
	//
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
		return 1;
	}
	//create window
	gWindow = SDL_CreateWindow("Bandcamp", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (gWindow == nullptr) {
		std::cout << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
		return  1;
	}
    //create renderer
    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(gRenderer == nullptr)
    {
        std::cout << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return 1;
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
            return 1;
        }
    }
	
	gScreenSurface = SDL_GetWindowSurface(gWindow);
	running = true;

	//create player
	return true;
}

void Game::loadMedia()
{
	sprites.push_back(Sprite(utils::loadTexture(gRenderer, "res/retroMe.png"), TILE_SIZE, TILE_SIZE));
}

void Game::update()
{
	//
}

void Game::draw()
{
	//SDL_RenderClear(gRenderer);
	for(auto i : sprites) {
		i.setPosition(SCREEN_WIDTH/2, SCREEN_HEIGHT/2);
		i.draw(gRenderer);
		//std::cout << sprites.size() << std::endl;
		//std::cout << i.getWidth() << std::endl;
	}
	SDL_RenderPresent(gRenderer);
}

//main game loop
void Game::run()
{
	//event handler
	SDL_Event e;
	
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