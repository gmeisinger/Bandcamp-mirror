#ifndef BANDCAMP_SPRITE_H_
#define BANDCAMP_SPRITE_H_

#include <SDL.h>
#include <SDL_image.h>

class Sprite
{
    private:
        SDL_Texture* texture;
        SDL_Rect img_rect;
    public:
        Sprite(SDL_Texture* texture, int _w, int _y);
        ~Sprite();
        void setPosition(int _x, int _y);
        int getWidth();
        int getHeight();
        void draw(SDL_Renderer* renderer);
};

#endif  //  BANDCAMP_SPRITE_H_