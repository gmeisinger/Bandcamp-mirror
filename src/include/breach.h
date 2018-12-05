#ifndef BANDCAMP_BREACH_H_
#define BANDCAMP_BREACH_H_

#include <algorithm>
#include <SDL.h>
#include <string>
#include <unordered_map>
#include <vector>

#include "object.h"
#include "randommap.h"
#include "utils.h"

class Breach : public Object
{
	private:
		char bType;
		SDL_Rect bRect;
		SDL_Rect bDrawBox;
		bool up;
	    bool down;
	    bool left;
	    bool right;
		int bNumber;
		bool bUsed;
		SDL_Texture* bImg;
		SDL_Rect bImgRect;
		SDL_Rect correction;
		
	public:
		void input(const Uint8* keystate);
		void init(SDL_Renderer *renderer);
		void update(std::unordered_map<std::string, Object*> &objectList, std::vector<std::vector<Tile*>> &grid, Uint32 ticks);
		std::string getInstanceName();
		SDL_Renderer* draw(SDL_Renderer *renderer, SDL_Rect cam);
		Breach(char type, SDL_Rect rect, SDL_Rect drawBox);
        ~Breach();
		Breach();
		void checkBreachOverlap(std::unordered_map<std::string, Object*> &objectList, std::vector<std::vector<Tile*>> &grid);
		SDL_Rect* getRect();
		void updatePosition();
		bool isUsed();
};

#endif  //  BANDCAMP_BREACH_H_