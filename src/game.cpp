/* Team Bandcamp
 * Class function: Contains core game funtions
 * 
*/

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
	GSM * gsm;
	screen_w = SCREEN_WIDTH;
	screen_h = SCREEN_HEIGHT;
	tile_s = TILE_SIZE;
}

/* Called from Main 
 * Set up the game
*/ 
bool Game::init() {
	
	// Initialize SDL 
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
		return false;
	}
	// 
	if(!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
		std::cout << "Warning: Linear texture filtering not enabled!" << std::endl;
	}
	
	/* Creating the window
	 * Arguments:
	 *   Window title
	 *   x position (we don't care in this example)
	 *   y position (we don't care in this example)
	 *   window width
	 *   window height
	 *   flags, see API for possible flags
	 */
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
		std::cout << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << std::endl;
		return false;
	}
	if( TTF_Init() == -1 )
    {
        std::cout << "SDL_ttf could not initialize! SDL_ttf Error: " << TTF_GetError() << std::endl;
        return false;
    }
	// Set renderer draw/clear color
	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
	
	
	//Start the GSM
  
  gsm = new GSM();
  
	gsm->init(gRenderer);
	
	// Initialization Successful
	running = true;
	return true;
}

// Game 
void Game::update(Uint32 ticks) {
	gsm->update(ticks);
}

// Updates image displayed to user 
void Game::draw() {
	//Clear the Screen
	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(gRenderer);
	
	//Draw the current Screen
	gRenderer = gsm->draw(gRenderer);
	SDL_RenderPresent(gRenderer);
}

/* keystate = a pointer to an array of key states.  1 means key depressed, 0 means not.  
 * Processes the updare 
*/
void Game::input(const Uint8* keystate){
	gsm->input(keystate);
}

//main game loop
void Game::run() {
	//event handler
	SDL_Event e;
	std::cout << "Running" << std::endl;
	//timer
	Uint32 last_time = SDL_GetTicks();
	Uint32 cur_time = 0;
	Uint32 ticks = 0;
	
	//main loop 
	while(running) {
		//handle events on queue
		while(SDL_PollEvent(&e) != 0) {
			//user requests quit
			if(e.type == SDL_QUIT) {
				running = false;
			}
		
		}
		
		// keystate = a pointer to an array of key states.  1 means key depressed, 0 means not.  
		const Uint8* keystate = SDL_GetKeyboardState( NULL );		// Should this be declared in constructor? 
		cur_time = SDL_GetTicks();
		ticks = cur_time - last_time;
		input(keystate);
		update(ticks);
		draw();
		last_time = cur_time;
	}
  
  

	//credits
	Credits creds = Credits(gRenderer);
	creds.load();
	creds.play();

	// Tear down and end.  Returns to main
	close();
}

// free memory and quit
// Returns main after completion
void Game::close() {
	
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
    gRenderer = nullptr;
	gWindow = nullptr;

	// Quit SDL subsystems
    IMG_Quit();
	SDL_Quit();
}
