#ifndef BANDCAMP_PLAYER_H_
#define BANDCAMP_PLAYER_H_

#include <SDL.h>
#include "object.h"


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
		
    public:
        Player(SDL_Rect _rect);
		Player();
        ~Player();
		void init(SDL_Renderer* gRenderer);
		void update(std::vector<Object*> objectList);
		void input(const Uint8* keystate);
		SDL_Renderer* draw(SDL_Renderer* gRenderer);
		
        void updateVelocity(int _xdv, int _ydv);
        void updatePosition();
        void checkBounds(int max_width, int max_height);
        int getWidth();
        int getHeight();
        int getX();
        int getY();
        SDL_Rect* getRect();
};

#endif  //  BANDCAMP_PLAYER_H_
