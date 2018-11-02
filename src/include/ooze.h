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
#include "collision.h"
#include "circle.h"
#include "game.h"
#include "pickup.h"

class Pickup;

enum oozeState {
    ROAMING,
    EATING,
    CLONING,
    FIGHTING,
    FLEEING,
    HIDING,
    DYING
};

class Ooze : public Object
{
private:
    //This should be removed ASAP
    SDL_Rect lWall;
    SDL_Rect rWall;
    SDL_Rect uWall;
    Circle cPillar;
    //
    SDL_Rect rect;

    int x_vel;
    int y_vel;
    int x_deltav;
    int y_deltav;

    oozeState state;
    int hostility;
    Player *player;
    HUD *hud;
    SpriteSheet sheet;
    Animation* anim;
    int overlapTicks;
    std::unordered_map<std::string, Animation> anims;
    int ate;
    SDL_Rect *target;
    
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
    
    // NEW
    Pickup* getPickup(std::unordered_map<std::string, Object*> *objectList);
    SDL_Rect* pickTarget(std::unordered_map<std::string, Object*> *objectList);
    bool foundFood(Pickup* pickUp);
    int getAte();

    // Updates
    void update(std::unordered_map<std::string, Object*> *objectList, Uint32 ticks);
    bool updateState(std::unordered_map<std::string, Object*> *objectList, Uint32 ticks);
    void updateVelocity(int _xdv, int _ydv); 
    void updatePosition();
    void updateAnimation(Uint32 ticks);
    // SDL
    std::string getInstanceName();
    void input(const Uint8* keystate);
    void init(SDL_Renderer* gRenderer);
    void setSpriteSheet(SDL_Texture* _sheet, int _cols, int _rows);
    void update(std::unordered_map<std::string, Object*> *objectList, std::vector<std::vector<int>> grid, Uint32 ticks);
    SDL_Renderer* draw(SDL_Renderer* renderer, SDL_Rect cam);
    bool checkOozeOverlap(std::unordered_map<std::string, Object*> *objectList, Uint32 ticks);
    bool isUsed();

    //Movement
    void checkBounds(int max_width, int max_height);
    void checkCollision(int curX, int curY);
    
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
    //void updateAnimation(Uint32 ticks);
};

#endif  //  OOZE_H_
