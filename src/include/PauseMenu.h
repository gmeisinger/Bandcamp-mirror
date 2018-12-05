#ifndef BANDCAMP_PAUSEMENU_H_
#define BANDCAMP_PAUSEMENU_H_

#include <SDL.h>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <string>

#include "global.h"
#include "utils.h"
#include "screen.h"
#include "spritesheet.h"
#include "artifact.h"

extern std::vector<Artifact*> artifactList; //The list of unique artifacts in the game.
extern int inventory[9][5];
extern int uniqueArtifactNumber; //How many unique artifacts are in the game?

class PauseMenu : public Screen 
{ 
	private:
		bool start;
		SpriteSheet sheet;
		std::unordered_map<std::string, Object*> objectList;
		SDL_Renderer* rendererReference;
		bool up, down, left, right, enter;
	public: 
		PauseMenu();
		void init(SDL_Renderer* renderer);
		void input(const Uint8* keystate);
		void update(Uint32 ticks);
		void setSpriteSheet(SDL_Texture* _sheet, int _cols, int _rows);
		SDL_Renderer* drawText(SDL_Renderer *renderer, int x, int y, int x_letterBound, int scale, std::string text);
		SDL_Renderer* draw(SDL_Renderer* renderer);
		void generateArtifactsList();
};

#endif  //  BANDCAMP_PAUSEMENU_H_
