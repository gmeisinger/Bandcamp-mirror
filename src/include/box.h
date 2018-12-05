#ifndef BANDCAMP_BOX_H_
#define BANDCAMP_BOX_H_

#include "game.h"
#include "utils.h"
#include "spritesheet.h"
#include "animation.h"
#include "object.h"

class Box : public Object
{
	private:
		SpriteSheet sheet;
		SDL_Texture* artifactImg;
		std::unordered_map<std::string, Animation> anims;
		Animation* anim;
		SDL_Rect boxRect; //The Collision Box
		SDL_Rect artifactImgRect;
		int toggleButton; //What state is the "Box open button"? 0 - not pressed  1 - pressed 1st frame 2 - held
		int instanceNumber = 0;
		int x_pos, y_pos; //X and Y according to the TILEMAP
		int state = 0; //State of the Box
		int frameTicks; //For animations

	public:
		//static int totalInstance;
		void input(const Uint8* keystate);
		void init(SDL_Renderer *renderer);
		void update(std::unordered_map<std::string, Object*> &objectList, std::vector<std::vector<Tile*>> &grid, Uint32 ticks);
		std::string getInstanceName();
		SDL_Renderer* draw(SDL_Renderer *renderer, SDL_Rect cam);
		Box(int x, int y);
        ~Box();
		Box();
		void checkOverlap(std::unordered_map<std::string, Object*> *objectList);
		void setSpriteSheet(SDL_Texture* _sheet, int _cols, int _rows);
		bool checkCanOpen(Player*& playerObj);
		void addAnimation(std::string tag, Animation anim);
		Animation* getAnimation(std::string tag);
		void setAnimation(std::string tag);
		bool isUsed();
		bool bulletCollision(std::unordered_map<std::string, Object*> &objectList);
		SDL_Rect* getRect();
};

#endif  //  BANDCAMP_BOX_H_