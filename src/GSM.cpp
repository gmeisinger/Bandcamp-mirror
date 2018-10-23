/* Team Bandcamp
 * Class function: 
 * 
*/

#include <SDL.h>
#include <SDL_image.h>

#include "include/GSM.h"
#include "include/credits.h"
#include "include/testroom.h"
#include "include/menu.h"

TestRoom testScreen;
int GSM::currentScreen = 0;
GSM::GSM(){
	currentScreen = 0;
	
	//Init Screens
	//They all get passed the pointer to the
	//Current Screen so they can change it when they see fit.
	testScreen = TestRoom();
	testMenu = new Menu();
	roomList.push_back(testMenu);
	roomList.push_back(&testScreen);
	previousScreen = 0;
	running = false;
}

void GSM::init(SDL_Renderer* reference){
	std::cout << "Init GSM" << std::endl;
	//When Objects need to load their sprites, they will be passed this renderer
	//As a reference for their init method.
	rendererReference = reference;
	
	roomList[currentScreen]->init(reference);
	running = true;
}

void GSM::update(Uint32 ticks){
	previousScreen = currentScreen;
	
	roomList[currentScreen]->update(ticks);
	
	//Checking if we changed screens this loop
	//If so, then call the init to the new screen.
	if(previousScreen != currentScreen)
		roomList[currentScreen]->init(rendererReference);
}

SDL_Renderer* GSM::draw(SDL_Renderer *renderer){
	return roomList[currentScreen]->draw(renderer);
}

void GSM::input(const Uint8* keystate){
	roomList[currentScreen]->input(keystate);
}