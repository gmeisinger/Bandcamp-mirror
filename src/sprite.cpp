#include "include/sprite.h"

//Constructor - takes a texture, width and height
Sprite::Sprite(SDL_Renderer* _renderer)
{
    renderer = _renderer;
    img_rect = {0,0,0,0};
}
//destructor
Sprite::~Sprite()
{
    SDL_DestroyTexture(texture);
    texture = nullptr;
}

bool Sprite::loadTexture(std::string fname, int w, int h)
{
    bool success = true;
    //load the image
    SDL_Surface* startSurf = IMG_Load(fname.c_str());
    if (startSurf == nullptr) {
        //std::cout << "Unable to load image " << fname << "! SDL Error: " << SDL_GetError() << std::endl;
        success = false;
    }
    //color key
    SDL_SetColorKey(startSurf, SDL_TRUE, SDL_MapRGB(startSurf->format, 0, 0xFF, 0xFF));
    //create texture from image
    this->texture = SDL_CreateTextureFromSurface(renderer, startSurf);
    if (texture == nullptr) {
        //std::cout << "Unable to create texture!" << std::endl;
        success = false;
    }

    this->img_rect.w = startSurf->w;
    this->img_rect.h = startSurf->h;
    //free original surface
    SDL_FreeSurface(startSurf);

    return success;
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

//void Sprite::setRect()
//draws the sprite to the screen at position x,y
void Sprite::draw()
{
    SDL_RenderCopy(renderer, texture, NULL, &img_rect);
}