/* Team Bandcamp
 * Class function:
 *
 */

#include "include/spritesheet.h"

SDL_Texture* texture;
std::vector< std::vector< SDL_Rect > > clips;

//
SpriteSheet::SpriteSheet(SDL_Texture* _texture) {
    texture = _texture;
}

//
SpriteSheet::SpriteSheet() {}

//
SpriteSheet::~SpriteSheet() {
    
}

/*	sets up clips for spritesheet
	takes number of columns and rows in sheet, as well as width and height of each frame
 */
void SpriteSheet::setClips(int _cols, int _rows, int _width, int _height) {
    for(int row=0;row<_rows;row++) {
        std::vector< SDL_Rect > curRow;
        for(int col=0;col<_cols;col++) {
            SDL_Rect clip = {col * _width, row * _height, _width, _height};
            curRow.push_back(clip);
        }
        clips.push_back(curRow);
    }
}

//
SDL_Texture* SpriteSheet::getTexture() {
    return texture;
}

/*	Returns rect at (x, y) of spritesheet
 */
SDL_Rect* SpriteSheet::get(int _x, int _y) {
    return &clips[_x][_y];
}

/*	Returns row of frames at _y
 */
std::vector<SDL_Rect> SpriteSheet::getRow(int _y) {
    return clips[_y];
}
