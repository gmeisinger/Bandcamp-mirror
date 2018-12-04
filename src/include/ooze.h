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
//#include "HUD.h"
//#include "player.h"
#include "collision.h"
#include "circle.h"
#include "global.h"
#include "pickup.h"
#include "tile.h"
#include "generator.h"
#include "tilemap.h"
#include "room.h"

class Pickup;

enum OozeState { // is public
        HANGRY, //temp state
        ROAMING,
        EATING,
        CLONING,
        FIGHTING,
        FLEEING,
        HIDING,
        DYING,
        ROOMEXIT,
        ROOMENTER
};

class Ooze : public Object {
    
    struct Stats {
        // Genetic statistics
        int health;
        int attack;
        int speed;
        int health_cost;
        int num_cost;
    };
    
    struct RoomTiles{
        SDL_Rect* startTile;
        SDL_Rect* endTile;
        SDL_Rect* door;
    };

private:
    SDL_Rect rect; // includes x_pos, y_pos, width, height
    //Used to check line of sight
    SDL_Rect colRect;
    SDL_Rect roomRect;

    int x_vel;
    int y_vel;
    int x_deltav;
    int y_deltav;
        
    Stats stats;
    RoomTiles roomTiles;

    OozeState state;
    int hostility;
//    Player *player;
//    HUD *hud;
    SpriteSheet sheet;
    Animation* anim;
    int overlapTicks;
    std::unordered_map<std::string, Animation> anims;
    int ate;
    SDL_Rect *target;

    Room* curRoom;
    Tilemap* tilemap;
    Tile* lastRoom;
    std::vector<Room*> neighbors;
    
    bool initialized;
    bool squeeze;
    int squeezeItr;
    std::vector<SDL_Rect> intersects;
    int iter;
    
public:

    

    // Variables
    int oozeNumber;         // This ooze's ID #
    static int totalOoze; //How many instances of the object exist? (initializes to 0)
    int damage = 5;
    // Constructors & destructor
    Ooze(); // Default constructor
    Ooze(Room* room, Tilemap* t);

//    Ooze(oozeState st, int hostil);
    Ooze(const Ooze& other);    // copy constructor
//    Ooze& operator=(Ooze other); // copy assignment
//    Ooze& operator=(rule_of_five&& other) noexcept // move assignment
//    Ooze(rule_of_five&& other) noexcept // move constructor
    ~Ooze(); // Destructor
    
    
    // NEW

    Pickup* getPickup(std::unordered_map<std::string, Object*> &objectList);
    SDL_Rect* pickTarget(std::unordered_map<std::string, Object*> &objectList, std::vector<std::vector<Tile*>> &grid);
    bool foundFood(Pickup* pickUp);
    int getAte();
    OozeState getState();
    void initRoom(std::vector<std::vector<Tile*>> &grid);

    // Updates
    bool updateState(std::unordered_map<std::string, Object*> &objectList, Uint32 ticks);
    void updateVelocity(int _xdv, int _ydv); 
    void updatePosition();
    void updateAnimation(Uint32 ticks);
    // SDL
    std::string getInstanceName();
    void input(const Uint8* keystate);
    void init(SDL_Renderer* gRenderer);
    void setSpriteSheet(SDL_Texture* _sheet, int _cols, int _rows);
    void update(std::unordered_map<std::string, Object*> &objectList, std::vector<std::vector<Tile*>> &grid, Uint32 ticks);
    SDL_Renderer* draw(SDL_Renderer* renderer, SDL_Rect cam);
    bool checkOozeOverlap(std::unordered_map<std::string, Object*> &objectList, Uint32 ticks);
    bool isUsed();

    //Movement

    void checkBounds(int max_width, int max_height, bool move);
    bool checkCollision(int curX, int curY, std::vector<std::vector<Tile*>> &grid, bool move);
    bool drawLine(std::vector<std::vector<Tile*>> &grid, SDL_Rect* target);
    void moveLine(std::vector<std::vector<Tile*>> &grid, SDL_Rect* target);
    void moveRoom(std::vector<std::vector<Tile*>> &grid);
    void switchRoom();
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
