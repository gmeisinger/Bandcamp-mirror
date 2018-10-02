#ifndef BANDCAMP_PLAYER_H_
#define BANDCAMP_PLAYER_H_

#include <SDL.h>

class Player
{
    private:
        SDL_Rect playerRect;
        int x_deltav;
        int y_deltav;
        int x_vel;
        int y_vel;
    public:
        Player(SDL_Rect _rect);
        ~Player();
        void updateVelocity(int _xdv, int _ydv);
        void updatePosition();
        void checkBounds(int max_width, int max_height);
        int getWidth();
        int getHeight();
        int getX();
        int getY();
        SDL_Rect* getRect();
        //void draw(SDL_Renderer* gRenderer);
};

#endif  //  BANDCAMP_PLAYER_H_