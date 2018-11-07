#ifndef BANDCAMP_PROJECTILE_H_
#define BANDCAMP_PROJECTILE_H_

#include <vector>
#include <unordered_map>
#include <SDL.h>
#include <string>

#include "player.h"
#include "object.h"

class Projectile : public Object
{
	private:
		SDL_Rect projRect;
		SDL_Rect projDrawBox;
		char projType;
		Player *projPlayer;

	public:
		void input(const Uint8* keystate);
		void init(SDL_Renderer *renderer);
		void update(std::unordered_map<std::string, Object*> *objectList, std::vector<std::vector<int>> grid, Uint32 ticks);
		std::string getInstanceName();
		SDL_Renderer* draw(SDL_Renderer *renderer, SDL_Rect cam);
		Projectile(SDL_Rect _rect, char type, Player* player);
        ~Projectile();
		Projectile();
		void checkProjOverlap(std::unordered_map<std::string, Object*> *objectList);
		SDL_Rect* getProjRect();
		void updatePosition(Uint32 ticks);
		bool isUsed();
};

#endif  //  BANDCAMP_PROJECTILE_H_