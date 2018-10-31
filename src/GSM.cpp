/* Team Bandcamp
 * Class function: Game state manger 
 * 
*/

#include <SDL.h>
#include <SDL_image.h>

#include "include/GSM.h"
#include "include/credits.h"
#include "include/testroom.h"
#include "include/PauseMenu.h"

int currentScreen = 0;
TestRoom testScreen;
PauseMenu pauseMenu;
bool pause;	//Is the game paused
int tempScreen; //What was the room before you paused?

GSM::GSM(){
	currentScreen = 0;	// Should describe this here 
	
	//Init Screens
	//They all get passed the pointer to the
	//Current Screen so they can change it when they see fit.
	testScreen = TestRoom();
	pauseMenu = PauseMenu();
	
	roomList.push_back(&testScreen);
	previousScreen = 0;
	pause = false;
	running = false;		// does this refer to the game running bool? its own from GSM.h
}

void GSM::init(SDL_Renderer* reference){
	//When Objects need to load their sprites, they will be passed this renderer
	//As a reference for their init method.
	rendererReference = reference;
	
	roomList[currentScreen]->init(reference);
	running = true;
}

void GSM::update(Uint32 ticks){
	previousScreen = currentScreen;
	
	if(pause)
		pauseMenu.update(ticks);
	else
		roomList[currentScreen]->update(ticks);
	
	//Checking if we changed screens this loop
	//If so, then call the init to the new screen.
	if(previousScreen != currentScreen)
	{	
		if(currentScreen == -1){ //The Pause Command
			pause = true;
			tempScreen = previousScreen;
			pauseMenu.init(rendererReference);
		}
		else if(currentScreen == -2){ //The Unpause Command
			pause = false;
			currentScreen = tempScreen;
		}
		else
			roomList[currentScreen]->init(rendererReference);
	}
}

SDL_Renderer* GSM::draw(SDL_Renderer *renderer){
	if(pause)
	{
		renderer = roomList[tempScreen]->draw(renderer); //So long as you don't put game logic in your draw method, this should work.
		renderer = pauseMenu.draw(renderer); //Draw the pause menu
	}
	else
		renderer = roomList[currentScreen]->draw(renderer);
	
	return renderer;	
}

void GSM::input(const Uint8* keystate){
	if(pause)
		pauseMenu.input(keystate);
	else
		roomList[currentScreen]->input(keystate);
}