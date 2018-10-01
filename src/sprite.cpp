#include "include/sprite.h"

//Constructor - takes a texture, width and height
Sprite::Sprite(SDL_Texture* _texture, int _width, int _height)
{
    texture = _texture;
    width = _width;
    height = _height;
}
//destructor
Sprite::~Sprite()
{
    SDL_DestroyTexture(texture);
    texture = nullptr;
}

//assign new texture to sprite
void Sprite::setTexture(SDL_Texture* _texture, int w, int h)
{
    texture = _texture;
    width = w;
    height = h;
}

//returns width of sprite
int Sprite::getWidth()
{
    return width;
}

//returns height of sprite
int Sprite::getHeight()
{
    return height;
}

//draws the sprite to the screen at position x,y
void Sprite::draw(SDL_Renderer* renderer, int x, int y)
{
    SDL_Rect dest_rect;
    dest_rect.x = x;
    dest_rect.y = y;
    dest_rect.w = this->width;
    dest_rect.h = this->height;
    SDL_RenderCopy(renderer, this->texture, NULL, &dest_rect);
}