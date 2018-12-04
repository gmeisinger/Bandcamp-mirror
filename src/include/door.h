#ifndef BANDCAMP_DOOR_H_
#define BANDCAMP_DOOR_H_

#include <vector>
#include <unordered_map>

#include "game.h"
#include "utils.h"
#include "spritesheet.h"
#include "animation.h"
#include "object.h"

class Door : public Object
{
	private:
		SpriteSheet sheet;
		std::unordered_map<std::string, Animation> anims;
		Animation* anim;
		SDL_Texture* openImg;
		SDL_Texture* closedImg;
		SDL_Rect doorRect; //The Collision Box
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
		std::vector<Room*> rooms;

	public:
		void input(const Uint8* keystate);
		void init(SDL_Renderer *renderer);
		void update(std::unordered_map<std::string, Object*> &objectList, std::vector<std::vector<Tile*>> &grid, Uint32 ticks);
		std::string getInstanceName();
		SDL_Renderer* draw(SDL_Renderer *renderer, SDL_Rect cam);
		Door(int x, int y, bool orientation);
		void addAnimation(std::string tag, Animation anim);	
		Animation* getAnimation(std::string tag);
		void setAnimation(std::string tag);
        SpriteSheet getSheet();
		void setSpriteSheet(SDL_Texture* _sheet, int _cols, int _rows);
		bool checkCanToggle(Player*& playerObj);
		bool isUsed();
        Door();
		~Door();
		Door(int x, int y);
		void addRoom(Room* _room);
		SDL_Rect* getRect();
};

#endif  //  BANDCAMP_DOOR_H_