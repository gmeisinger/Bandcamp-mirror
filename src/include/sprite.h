#ifndef BANDCAMP_SPRITE_H_
#define BANDCAMP_SPRITE_H_

#include <SDL.h>
#include <SDL_image.h>
#include <string>

class Sprite
{
    private:
        SDL_Renderer* renderer;
        SDL_Texture* texture;
        SDL_Rect img_rect;
    public:
        Sprite(SDL_Renderer* _renderer);
        ~Sprite();
        bool loadTexture(std::string fname, int w, int h);
        void setPosition(int _x, int _y);
        int getWidth();
        int getHeight();
        void draw();
};

#endif  //  BANDCAMP_SPRITE_H_