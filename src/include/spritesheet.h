#ifndef BANDCAMP_SPRITESHEET_H_
#define BANDCAMP_SPRITESHEET_H_

#include <SDL.h>
#include <vector>

class SpriteSheet
{
private:
    SDL_Texture* texture;
    std::vector< std::vector < SDL_Rect > > clips;
public:
    SpriteSheet(SDL_Texture* _texture);
    SpriteSheet();
    ~SpriteSheet();
    void setClips(int _cols, int _rows, int _width, int _height);
    SDL_Rect* get(int _x, int _y);
    std::vector<SDL_Rect> getRow(int _y);
    SDL_Texture* getTexture();
};

#endif  //  BANDCAMP_SPRITESHEET_H_
