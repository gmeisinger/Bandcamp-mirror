#ifndef BANDCAMP_PROJECTILE_H_
#define BANDCAMP_PROJECTILE_H_

#include <algorithm>
#include <SDL.h>
#include <string>
#include <unordered_map>
#include <vector>

#include "collision.h"
#include "object.h"
#include "utils.h"

class Projectile : public Object
{
	private:
		SDL_Rect projRect;
		SDL_Rect projDrawBox;
		char projType;

	public:
		void input(const Uint8* keystate);
		void init(SDL_Renderer *renderer);
		void update(std::unordered_map<std::string, Object*> *objectList, std::vector<std::vector<int>> grid, Uint32 ticks);
		std::string getInstanceName();
		SDL_Renderer* draw(SDL_Renderer *renderer, SDL_Rect cam);
		Projectile(char type);
        ~Projectile();
		Projectile();
		void checkProjOverlap(int curX, int curY, std::vector<std::vector<int>> grid);
		SDL_Rect* getProjRect();
		void updatePosition(Uint32 ticks);
		bool isUsed();
};

#endif  //  BANDCAMP_PROJECTILE_H_