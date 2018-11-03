#ifndef BANDCAMP_DOOR_H_
#define BANDCAMP_DOOR_H_

#include <vector>
#include <unordered_map>

#include "utils.h"
#include "spritesheet.h"
#include "animation.h"

class Player;

class Pickup : public Object
{
	private:
		SpriteSheet sheet;
		Animation* anim;
		SDL_Texture* openImg, closedImg;
		SDL_Rect doorRect, playerBox; //The Collision Box
		static int totalInstance = 0;//How many instances of the object exist?
		int toggleButton = 0; //What state is the "Door open button"? 0 - not pressed  1 - pressed 1st frame 2 - held
		int instanceNumber = 0;
		int x_pos, y_pos; //X and Y according to the TILEMAP
		int state = 0; //State of the Door
		/*
			0 - Closed
			1 - Sliding
			2 - Open
		*/
		bool directionLR = false; //F - Up/Down T - L/R
		bool foundPlayer; //Do we have a reference to the player?

	public:
		void input(const Uint8* keystate);
		void init(SDL_Renderer *renderer);
		void update(std::unordered_map<std::string, Object*> *objectList, std::vector<std::vector<int>> grid, Uint32 ticks);
		std::string getInstanceName();
		SDL_Renderer* draw(SDL_Renderer *renderer, SDL_Rect cam);
		Door(int x, int y, bool isOpen);
        ~Door();
		Door();
};

#endif  //  BANDCAMP_DOOR_H_