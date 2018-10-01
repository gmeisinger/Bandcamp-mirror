#include "include/sprite.h"

//Constructor - takes a texture, width and height
Sprite::Sprite(SDL_Texture* _texture, int _width, int _height)
{
    texture = _texture;
    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
    img_rect.x = 0;
    img_rect.y = 0;
    img_rect.w = _width;
    img_rect.h = _height;
}
//destructor
Sprite::~Sprite()
{
    SDL_DestroyTexture(texture);
    texture = nullptr;
}


//returns width of sprite
int Sprite::getWidth()
{
    return img_rect.w;
}

//returns height of sprite
int Sprite::getHeight()
{
    return img_rect.h;
}

//set position
void Sprite::setPosition(int _x, int _y)
{
    img_rect.x = _x;
    img_rect.y = _y;
}
//draws the sprite to the screen at position x,y
void Sprite::draw(SDL_Renderer* renderer)
{
    SDL_RenderCopy(renderer, this->texture, NULL, &this->img_rect);
}