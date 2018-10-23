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
#include "HUD.h"
#include "player.h"


enum oozeState { roaming, eating, attacking, approaching, retreating, dying, inCrack};

class Ooze : public Object
{
private:
    SDL_Rect rect;
    oozeState state;
    int hostility;
    Player *oozePlayer;
    HUD *hud;
    SpriteSheet sheet;
    Animation* anim;
    int overlapTicks;
    std::unordered_map<std::string, Animation> anims;
    
public:
    // Variables
    int oozeNumber;         // This ooze's ID #
    static int totalOoze; //How many instances of the object exist? (initializes to 0)
    int damage = 5;
    // Constructors & destructor
    Ooze();
    Ooze(SDL_Rect _rect, Player *player, HUD *h);
//    Ooze(oozeState st, int hostil);
    ~Ooze();
    
    // SDL
    std::string getInstanceName();
    void input(const Uint8* keystate);
    void init(SDL_Renderer* gRenderer);
    void setSpriteSheet(SDL_Texture* _sheet, int _cols, int _rows);
    void update(std::unordered_map<std::string, Object*> *objectList, Uint32 ticks);
    SDL_Renderer* draw(SDL_Renderer* renderer);
    void checkOozeOverlap(std::unordered_map<std::string, Object*> *objectList, Uint32 ticks);
    bool isUsed();
    
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
    SpriteSheet getSheet();
    //Animation
    void addAnimation(std::string tag, Animation anim);
    Animation* getAnimation(std::string tag);
    void setAnimation(std::string tag);
    void updateAnimation(Uint32 ticks);

};

#endif  //  OOZE_H_
