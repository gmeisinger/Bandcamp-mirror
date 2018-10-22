#ifndef OOZE_H_
#define OOZE_H_

#include <SDL.h>
#include <unordered_map>
#include <vector>
#include <cmath>
#include "object.h"
#include "spritesheet.h"
#include "animation.h"
#include "utils.h"

enum State { roaming, eating, attacking, approaching, retreating, dying, inCrack};
//int numOozes = 0;

//
class Ooze : public Object
{
private:
    SDL_Rect oozeRect;
    State state;
    int hostility;
    //Player *player;
    
public:
    SpriteSheet sheet;
    Animation* animation;
    // Constructors & destructor
    Ooze();
    Ooze(SDL_Rect _rect);
//    Ooze(State st, int hostil);
    ~Ooze();
    
    // SDL
    std::string getInstanceName();
    void input(const Uint8* keystate);
    void init(SDL_Renderer* gRenderer);
    void setSpriteSheet(SDL_Texture* _sheet, int _cols, int _rows);
    void update(std::unordered_map<std::string, Object*> *objectList, Uint32 ticks);
    SDL_Renderer* draw(SDL_Renderer* renderer);
    bool isUsed();

//    std::unordered_map<std::string, Animation> anims;
    
    // Math
    void increaseHostility();
    void decreaseHostility();
//    bool checkPlayerDistance(std::vector<Object*> objectList);
    // Getters
    SpriteSheet getSheet();
    int getWidth();
    int getHeight();
    int getX();
    int getY();
    SDL_Rect* getRect();
//    void addAnimation(std::string tag, Animation anim);
//    Animation* getAnimation(std::string tag);
//    void setAnimation(std::string tag);
//    void updateAnimation(Uint32 ticks);
//    SpriteSheet getSheet();

};

#endif  //  OOZE_H_
