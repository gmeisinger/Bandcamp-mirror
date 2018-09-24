#ifndef BANDCAMP_SPRITE_H_
#define BANDCAMP_SPRITE_H_

#include <SDL2/SDL.h>

class Sprite
{
    private:
        SDL_Texture* texture;
        int width;
        int height;
    public:
        Sprite(SDL_Texture* texture, int w, int y);
        //~Sprite();
        void setTexture(SDL_Texture* texture, int w, int h);
        int getWidth();
        int getHeight();
        void draw(SDL_Renderer* renderer, int x, int y);
};

#endif  //  BANDCAMP_SPRITE_H_