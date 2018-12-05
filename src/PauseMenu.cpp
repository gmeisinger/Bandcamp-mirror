/* Team Bandcamp
 * Class function: 
 * This is the Pause Menu
 * 
*/

#include <random>
#include "include/spritesheet.h"
#include "include/PauseMenu.h"
#include "include/game.h"

std::vector<SDL_Texture*> menuGraphics;
std::vector<SDL_Texture*> rareArtifactImgs;
SDL_Texture* rareArtifact;
SDL_Texture* currentArtifactImg;
int currentR, currentG, currentB;
std::string currentArtifactText; // The string that should be drawn to the screen.
int menuState;
SDL_Rect menuImg, aMenuImg, aMenuAImg, aMenuCursorImg, menuImg2, cursor;
bool startHeld, gen_d;
int keyHeld [7]; // 0 - not pressed, 1 - first frame 2 - held
int inventorySizeX = 9;
int inventorySizeY = 5;
int currentX = 0;
int currentY = 0;
std::vector<Artifact*> artifactList; //The list of unique artifacts in the game.
int inventory[9][5];
int uniqueArtifactNumber = 45; //How many unique artifacts are in the game?

PauseMenu::PauseMenu(): Screen()
{	
	gen_d = false;
	//Clear the array
	for(int x = 0; x < inventorySizeX; x++){
		for(int y = 0; y < inventorySizeY; y++){
			inventory[x][y] = -1;
		}
	}
	
	/*
	std::random_device rd;  //Will be used to obtain a seed for the random number engine
	std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
	gen.seed(time(NULL));
	std::uniform_int_distribution<> artifactDis(0, uniqueArtifactNumber-1);
	
	//Test Fill array
	for(int x1 = 0; x1 < inventorySizeX; x1++){
		for(int y1 = 0; y1 < inventorySizeY; y1++){
			inventory[x1][y1] = artifactDis(gen);
		}
	}*/
}

/* Summary
 * Argument  
 *
*/
void PauseMenu::init(SDL_Renderer* reference){
	rendererReference = reference;
	menuState = 0;
	menuGraphics.push_back(utils::loadTexture(rendererReference, "res/artifactMenu.png"));
	menuGraphics.push_back(utils::loadTexture(rendererReference, "res/artifactMenu_cursor.png"));
	aMenuImg = {70, 107, 660, 378};
	aMenuCursorImg = {310, 208, 50, 50};
	aMenuAImg = {111, 141, 164, 153};
	currentX = 0;	
	currentY = 0;
	
	for(int x = 1; x <= 10; x++)
	{
		std::ostringstream path;
		path << "res/rareArt/rareArtifact_";
		path << x;
		path << ".png";
		rareArtifactImgs.push_back(utils::loadTexture(rendererReference, path.str()));
	}
	
	if(!gen_d)
	{
		gen_d = true;
		generateArtifactsList();
	}
	
	/*
	menuGraphics.push_back(utils::loadTexture(rendererReference, "res/cursor.png"));
	menuImg = {SCREEN_WIDTH/2-275, SCREEN_HEIGHT/2-100, 550, 200};
	menuImg2 = {SCREEN_WIDTH/2-250, SCREEN_HEIGHT/2-80, 550, 200};
	*/
	
	//Font
	setSpriteSheet(utils::loadTexture(rendererReference, "res/font.png"), 26, 1);
	
	cursor = {SCREEN_WIDTH/2-208, SCREEN_HEIGHT/2, 28, 28}; //Reset the cursor position
	startHeld = true;
}

void PauseMenu::setSpriteSheet(SDL_Texture* _sheet, int _cols, int _rows) {
    sheet = SpriteSheet(_sheet);
    sheet.setClips(_cols, _rows, 11, 15);	
}

/* Summary
 * Argument  
 *
*/
void PauseMenu::update(Uint32 ticks){
	//When the actual menu is implemented, cursor placement can be handled a different way.
	
	switch(menuState){
		case 0: //Artifact Menu
			if(keyHeld[6] == 1) //Enter Pressed
				GSM::currentScreen = -2; //Unpause <- Its an arbitrary number.
			
			if (keyHeld[3] == 1 && currentX < inventorySizeX-1) //Right
			{
				aMenuCursorImg.x += 42;
				currentX++;
			}
			else if(keyHeld[2] == 1 && currentX > 0) //Left
			{
				aMenuCursorImg.x -= 42;
				currentX--;
			}
			else if (keyHeld[1] == 1 && currentY < inventorySizeY-1) //Down
			{
				aMenuCursorImg.y += 42;
				currentY++;
			}
			else if(keyHeld[0] == 1 && currentY > 0) //Up
			{
				aMenuCursorImg.y -= 42;
				currentY--;
			}
		
			//Check if there is something to write
			if(inventory[currentX][currentY] != -1)
			{
				currentArtifactText = artifactList.at(inventory[currentX][currentY])->getName();
				currentArtifactImg = artifactList.at(inventory[currentX][currentY])->getImage();
				currentR = artifactList.at(inventory[currentX][currentY])->getR();
				currentG = artifactList.at(inventory[currentX][currentY])->getG();
				currentB = artifactList.at(inventory[currentX][currentY])->getB();			
			}
			else
				currentArtifactText = "";
		
			break;
		
		
		/*	else if (keyHeld[3] == 1 || keyHeld[2] == 1){ //Right or Left Pressed (This is a hack solution)
				if(cursor.x == SCREEN_WIDTH/2-208)
					cursor.x = SCREEN_WIDTH/2;
				else
					cursor.x = SCREEN_WIDTH/2-208;
			}
			else if(keyHeld[4] == 1){ //Confirm Pressed
				cursor.x = SCREEN_WIDTH/2 - 218;
				cursor.y = SCREEN_HEIGHT/2 + 2;
				menuState = 1; //GOTO the second window.
			}
		break;
		
		case 1: //Second Window
			if(keyHeld[6] == 1) //Enter Pressed
				GSM::currentScreen = -2; //Unpause <- Its an arbitrary number.
			else if (keyHeld[3] == 1){ //Right Pressed
				if(cursor.x == SCREEN_WIDTH/2 - 218){
					cursor.x = SCREEN_WIDTH/2 + 90;
					cursor.y = SCREEN_HEIGHT/2+ 20;
				}
				else if(cursor.x == SCREEN_WIDTH/2 + 90){
					cursor.x = SCREEN_WIDTH/2 - 97;
					cursor.y = SCREEN_HEIGHT/2 + 49;
				}
				else{
					cursor.x = SCREEN_WIDTH/2 - 218;
					cursor.y = SCREEN_HEIGHT/2 + 2;
				}
					
			}
			else if(keyHeld[2] == 1){  //Left Pressed
				if(cursor.x == SCREEN_WIDTH/2 - 218){
					cursor.x = SCREEN_WIDTH/2 - 97;
					cursor.y = SCREEN_HEIGHT/2 + 49;
					
					
				}
				else if(cursor.x == SCREEN_WIDTH/2 + 90){
					cursor.x = SCREEN_WIDTH/2 - 218;
					cursor.y = SCREEN_HEIGHT/2 + 2;
				}
				else{
					cursor.x = SCREEN_WIDTH/2 + 90;
					cursor.y = SCREEN_HEIGHT/2 + 20;
				}
			}
			else if(keyHeld[5] == 1){ //Back Pressed
				cursor.x = SCREEN_WIDTH/2-208;
				cursor.y = SCREEN_HEIGHT/2;
				menuState = 0; //GOTO the initial window.
			}
		break;*/
	}
}

/* Summary
 * Argument  
 *
*/
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

/* Summary
 * Argument  
 *
*/
SDL_Renderer* PauseMenu::draw(SDL_Renderer *renderer){
	switch(menuState){
		case 0: //Initial Window
			SDL_RenderCopy(renderer, menuGraphics.at(0), NULL, &aMenuImg); //The artifactMenu
			drawText(renderer, int(aMenuImg.w*.37)+aMenuImg.x, int(aMenuImg.h*.093)+aMenuImg.y, 20, 2, "artifact menu");
			drawText(renderer, 106, 306, 17, 1, currentArtifactText);
			SDL_Rect img = {315, 213, 40, 40};
			
			for(int y1 = 0; y1 < inventorySizeY; y1++){
				for(int x1 = 0; x1 < inventorySizeX; x1++){
					if(inventory[x1][y1] != -1)
					{
						Artifact* art = artifactList.at(inventory[x1][y1]);
						
						SDL_SetTextureColorMod(art->getImage(), art->getR(), art->getG(), art->getB());
						SDL_RenderCopy(renderer, artifactList.at(inventory[x1][y1])->getImage(), NULL, &img);
					}
					img.x += 42;
				}
				img.x = 315;
				img.y += 42;
			}
			
			if(currentArtifactText != "")
			{
				SDL_SetTextureColorMod(currentArtifactImg, currentR, currentG, currentB);
				SDL_RenderCopy(renderer, currentArtifactImg, NULL, &aMenuAImg);
			}
			
			SDL_RenderCopy(renderer, menuGraphics.at(1), NULL, &aMenuCursorImg); //artifactMenu Cursor
		break;
		
		/*
			SDL_RenderCopy(renderer, menuGraphics.at(0), NULL, &menuImg); //The menu Window
			SDL_RenderCopy(renderer, menuGraphics.at(2), NULL, &cursor);
		break;
		
		case 1:
			SDL_RenderCopy(renderer, menuGraphics.at(0), NULL, &menuImg); //The menu Window behind 
			SDL_RenderCopy(renderer, menuGraphics.at(1), NULL, &menuImg2); //The 2nd Window
			SDL_RenderCopy(renderer, menuGraphics.at(2), NULL, &cursor);
		break;*/
	}
	
	return renderer;
}

/*
	renderer - the renderer
	x - starting x
	y - starting y 
	x_letterBound - how many letters do you want per line (This works because the font is monospace.)
	scale - font scale
	text - the string
*/
SDL_Renderer* PauseMenu::drawText(SDL_Renderer *renderer, int x, int y, int x_letterBound, int scale, std::string text)
{
	int letter_w = 11*scale;
	int letter_h = 15*scale;
	
	SDL_Rect* dest = new SDL_Rect;
    dest->w = letter_w;
    dest->h = letter_h;
	dest->x = x;
	dest->y = y;
	
	int letter; //Index of letters
	
	for(int a = 0; a < text.length(); a++)
	{
		//Wrap the text
		if(dest->x + letter_w > x+x_letterBound*letter_w)
		{
			dest->y += letter_h;
			dest->x = x;
		}
		
		//Lowercase a-z
		letter = int(text.at(a))-97;
		
		//Nothing for spaces
		if(letter >= 0)
			SDL_RenderCopy(renderer, sheet.getTexture(), sheet.get(0, letter), dest);
		
		dest->x += letter_w;
		

	}
}

void PauseMenu::generateArtifactsList()
{
	int adjssize = 11;
	int nounssize = 12;
	std::string adjs[adjssize] = {"blue", "rusted", "crusty", "spongey", "pathetic", "cursed", "unisex", "sad", "spicy", "broken", "saucy"};
	std::string nouns[nounssize] = {"bag", "machine part", "broom", "bat", "dice", "image", "abacus", "mistake", "sauce", "salmon", "meat", "sock"};
	
	std::random_device rd;  //Will be used to obtain a seed for the random number engine
	std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
	gen.seed(time(NULL));
	std::uniform_int_distribution<> adjDis(0, adjssize-1);
	std::uniform_int_distribution<> nounDis(0, nounssize-1);
	std::uniform_int_distribution<> colorDis(30, 255);
	std::uniform_int_distribution<> aImgDis(0, rareArtifactImgs.size()-1);
	
	for(int x = 0; x < uniqueArtifactNumber; x++)
	{
		std::string title = adjs[adjDis(gen)]+" "+nouns[nounDis(gen)];
		
		int r = colorDis(gen);
		int g = colorDis(gen);
		int b = colorDis(gen);
		int imgIndex = aImgDis(gen);
		
		artifactList.push_back(new Artifact(title, rareArtifactImgs.at(imgIndex), r, g, b));
	}
	
	
}

