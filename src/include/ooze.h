#ifndef OOZE_H_
#define OOZE_H_

#include <SDL.h>
#include <unordered_map>
#include <vector>
#include <cmath>
#include "object.h"
#include "spritesheet.h"
#include "animation.h"

enum State { roaming, eating, attacking, approaching, retreating, dying, inCrack};
int numOozes = 0;

//
class Ooze //: public Object
{
private:
    SDL_Rect enemyRect;
    State state;
    int hostility;
    //Player *player;
    
public:
    SpriteSheet sheet;
    Animation* animation;
    // Constructors & destructor
    Ooze();
//    Ooze(State st, int hostil);
    ~Ooze();
    
    //object.h virtuals
// 		virtual void input(const Uint8* keystate) = 0;
//    virtual void init(SDL_Renderer *renderer) = 0;
//    virtual void update(std::vector<Object*> objectList, Uint32 ticks) = 0;
//    virtual SDL_Renderer* draw(SDL_Renderer *renderer) = 0;
    
    
    // SDL
    void update(std::vector<Object*> objectList, Uint32 ticks);
//    SDL_Renderer* draw(SDL_Renderer *renderer);
//    std::unordered_map<std::string, Animation> anims;
    
    // Math
    void increaseHostility();
    void decreaseHostility();
//    bool checkPlayerDistance(std::vector<Object*> objectList);
    // Getters
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
