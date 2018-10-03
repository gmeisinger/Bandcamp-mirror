#include "include/game.h"
#include "include/player.h"
#include "include/HUD.h"
//#include "include/sprite.h"

constexpr int SCREEN_WIDTH = 800;
constexpr int SCREEN_HEIGHT = 600;
constexpr int TILE_SIZE = 32;

SDL_Rect player_box = {SCREEN_WIDTH/2-TILE_SIZE/2, SCREEN_HEIGHT/2-TILE_SIZE/2, TILE_SIZE, TILE_SIZE};
Player temp_player = Player(player_box);

//Constructor
//starts new game
Game::Game()
{
	gWindow = nullptr;
	gRenderer = nullptr;
	running = false;
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
	running = true;
	return true;
}


void Game::loadMedia() {
	//Player temp_player = Player(&player_box);

	//Sprite new_sprite = Sprite(gRenderer);
	//new_sprite.loadTexture("res/retroMe.png", TILE_SIZE, TILE_SIZE);
	//new_sprite.setPosition(100,100);
	//sprites.push_back(new_sprite);
}

void Game::update() {
	updatePlayer();
}

void Game::updatePlayer() {
	int x_deltav = 0;
	int y_deltav = 0;

	// Get array of current key states
	// Note that array is indexed by scancodes, not keycodes
	// https://wiki.libsdl.org/SDL_Scancode
	const Uint8* keystate = SDL_GetKeyboardState(nullptr);
	if (keystate[SDL_SCANCODE_W])
		y_deltav -= 1;
	if (keystate[SDL_SCANCODE_A])
		x_deltav -= 1;
	if (keystate[SDL_SCANCODE_S])
		y_deltav += 1;
	if (keystate[SDL_SCANCODE_D])
		x_deltav += 1;

	temp_player.updateVelocity(x_deltav, y_deltav);

	// Move box
	temp_player.updatePosition();

	// Check you haven't moved off the screen
	temp_player.checkBounds(SCREEN_WIDTH, SCREEN_HEIGHT);
}

void Game::draw() {
	SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
	SDL_RenderClear(gRenderer);
	//for(auto i : sprites) {
		//i.setPosition(SCREEN_WIDTH/2, SCREEN_HEIGHT/2);
	//	i.draw();
		//std::cout << sprites.size() << std::endl;
		//std::cout << i.getWidth() << std::endl;
	//}
	SDL_SetRenderDrawColor(gRenderer, 0x00, 0xFF, 0x00, 0xFF);
	SDL_RenderFillRect(gRenderer, temp_player.getRect());

	//Commented out because presentation is finalized in HUD
	//SDL_RenderPresent(gRenderer);
}

//main game loop
void Game::run() {
	//event handler
	SDL_Event e;

	//Initialize HUD
	HUD gameHud = HUD(gRenderer);
	gameHud.init_HUD();

	int temperature = 100;
	int oxygen = 100;

	//main loop
	while(running) {
		//handle events on queue
		while(SDL_PollEvent(&e) != 0) {
			//user requests quit
			if(e.type == SDL_QUIT) {
				running = false;
			}
		
		}

		oxygen -= 1;
		temperature -= 1;
		if(oxygen == 0){
			oxygen = 100;
		}
		if(temperature == 0){
			temperature = 100;
		}
		
		update();
		draw();
		gameHud.change_levels(oxygen, temperature);
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