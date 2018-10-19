#ifndef BANDCAMP_PLAYER_H_
#define BANDCAMP_PLAYER_H_

#include <SDL.h>
#include <unordered_map>
#include <cmath>
#include <string>
#include "object.h"
#include "spritesheet.h"
#include "animation.h"


class Player : public Object
{
    private:
        SDL_Rect playerRect;
        int x_deltav;
        int y_deltav;
        int x_vel;
        int y_vel;
		bool up;
		bool down;
		bool left;
		bool right;
		SpriteSheet sheet;
        std::unordered_map<std::string, Animation> anims;
        Animation* anim;
		
    public:
        Player(SDL_Rect _rect);
		Player();
        ~Player();
		std::string getInstanceName();
		void init(SDL_Renderer* gRenderer);
		void update(std::vector<Object*> *objectList, Uint32 ticks);
		void input(const Uint8* keystate);
		SDL_Renderer* draw(SDL_Renderer* gRenderer);
		void setSpriteSheet(SDL_Texture* _sheet, int _cols, int _rows);
        void updateVelocity(int _xdv, int _ydv);
        void updatePosition();
        void checkBounds(int max_width, int max_height);
        int getWidth();
        int getHeight();
        int getX();
        int getY();
        SDL_Rect* getRect();
        void addAnimation(std::string tag, Animation anim);
        Animation* getAnimation(std::string tag);
        void setAnimation(std::string tag);
        void updateAnimation(Uint32 ticks);
        SpriteSheet getSheet();
};

#endif  //  BANDCAMP_PLAYER_H_
