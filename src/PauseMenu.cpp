/* Team Bandcamp
 * Class function: 
 * This is the Pause Menu
 * 
*/

#include <SDL.h>
#include <algorithm>
#include <string>

#include "include/spritesheet.h"
#include "include/PauseMenu.h"
#include "include/game.h"

std::vector<SDL_Texture*> menuGraphics;
int menuState;
SDL_Rect menuImg, menuImg2, cursor;
bool startHeld;
int keyHeld [7]; // 0 - not pressed, 1 - first frame 2 - held

PauseMenu::PauseMenu(): Screen(){start = false;}

void PauseMenu::init(SDL_Renderer* reference){
	rendererReference = reference;
	menuState = 0;
	menuGraphics.push_back(utils::loadTexture(rendererReference, "res/Test Window.png")); //These images look really different on purpose.
	menuGraphics.push_back(utils::loadTexture(rendererReference, "res/Test Window - 2.png")); //These images look really different on purpose.
	menuGraphics.push_back(utils::loadTexture(rendererReference, "res/Cursor.png"));
	menuImg = {screen_w/2-275, screen_h/2-100, 550, 200};
	menuImg2 = {screen_w/2-250, screen_h/2-80, 550, 200};
	cursor = {screen_w/2-208, screen_h/2, 28, 28}; //Reset the cursor position
	startHeld = true;
}

void PauseMenu::update(Uint32 ticks){
	//When the actual menu is implemented, cursor placement can be handled a different way.
	
	switch(menuState){
		case 0: //Initial Window
			if(keyHeld[6] == 1) //Enter Pressed
				currentScreen = -2; //Unpause <- Its an arbitrary number.
			else if (keyHeld[3] == 1 || keyHeld[2] == 1){ //Right or Left Pressed (This is a hack solution)
				if(cursor.x == screen_w/2-208)
					cursor.x = screen_w/2;
				else
					cursor.x = screen_w/2-208;
			}
			else if(keyHeld[4] == 1){ //Confirm Pressed
				cursor.x = screen_w/2 - 238;
				cursor.y = screen_h/2 - 5;
				menuState = 1; //GOTO the second window.
			}
		break;
		
		case 1: //Second Window
			if(keyHeld[6] == 1) //Enter Pressed
				currentScreen = -2; //Unpause <- Its an arbitrary number.
			else if (keyHeld[3] == 1){ //Right Pressed
				if(cursor.x == screen_w/2 - 238){
					cursor.x = screen_w/2 + 70;
					cursor.y = screen_h/2;
				}
				else if(cursor.x == screen_w/2 + 70){
					cursor.x = screen_w/2 - 117;
					cursor.y = screen_h/2 + 29;
				}
				else{
					cursor.x = screen_w/2 - 238;
					cursor.y = screen_h/2 - 5;
				}
					
			}
			else if(keyHeld[2] == 1){  //Left Pressed
				if(cursor.x == screen_w/2 - 238){
					cursor.x = screen_w/2 - 117;
					cursor.y = screen_h/2 + 29;
					
					
				}
				else if(cursor.x == screen_w/2 + 70){
					cursor.x = screen_w/2 - 238;
					cursor.y = screen_h/2 - 5;
				}
				else{
					cursor.x = screen_w/2 + 70;
					cursor.y = screen_h/2;
				}
			}
			else if(keyHeld[5] == 1){ //Back Pressed
				cursor.x == screen_w/2-208;
				cursor.y = screen_h/2;
				menuState = 0; //GOTO the initial window.
			}
		break;
	}
}

void PauseMenu::input(const Uint8* keystate){
	/*
		0 - W      - Up
		1 - S      - Down
		2 - A      - Left
		3 - D      - Right
		4 - Z      - Confirm
		5 - X 	   - Back
		6 - Return - Start Button
	*/
	
	if(keystate[SDL_SCANCODE_W])
	{
		if(keyHeld[0] >= 1)
			keyHeld[0] = 2;
		else
			keyHeld[0] = 1;
	}
	else
		keyHeld[0] = 0;
	
	if(keystate[SDL_SCANCODE_S])
	{
		if(keyHeld[1] >= 1)
			keyHeld[1] = 2;
		else
			keyHeld[1] = 1;
	}
	else
		keyHeld[1] = 0;
	
	if(keystate[SDL_SCANCODE_A])
	{
		if(keyHeld[2] >= 1)
			keyHeld[2] = 2;
		else
			keyHeld[2] = 1;
	}
	else
		keyHeld[2] = 0;
	
	if(keystate[SDL_SCANCODE_D])
	{
		if(keyHeld[3] >= 1)
			keyHeld[3] = 2;
		else
			keyHeld[3] = 1;
	}
	else
		keyHeld[3] = 0;
	
	if(keystate[SDL_SCANCODE_Z])
	{
		if(keyHeld[4] >= 1)
			keyHeld[4] = 2;
		else
			keyHeld[4] = 1;
	}
	else
		keyHeld[4] = 0;
	
	if(keystate[SDL_SCANCODE_X])
	{
		if(keyHeld[5] >= 1)
			keyHeld[5] = 2;
		else
			keyHeld[5] = 1;
	}
	else
		keyHeld[5] = 0;
	
	if(keystate[SDL_SCANCODE_RETURN])
	{
		//When you come back into the room after a pause, you will most likely still be holding down
		//the enter key. This prevents you from going straight back into the pause menu.
		if(startHeld)
		{
			keyHeld[6] = 2;
			startHeld = false;
		}
		else
		{
			if(keyHeld[6] >= 1)
				keyHeld[6] = 2;
			else
				keyHeld[6] = 1;
		}
	}
	else
		keyHeld[6] = 0;
}

SDL_Renderer* PauseMenu::draw(SDL_Renderer *renderer){
	switch(menuState){
		case 0: //Initial Window
			SDL_RenderCopy(renderer, menuGraphics.at(0), NULL, &menuImg); //The menu Window
			SDL_RenderCopy(renderer, menuGraphics.at(2), NULL, &cursor);
		break;
		
		case 1:
			SDL_RenderCopy(renderer, menuGraphics.at(0), NULL, &menuImg); //The menu Window behind 
			SDL_RenderCopy(renderer, menuGraphics.at(1), NULL, &menuImg2); //The 2nd Window
			SDL_RenderCopy(renderer, menuGraphics.at(2), NULL, &cursor);
		break;
	}
	
	return renderer;
}