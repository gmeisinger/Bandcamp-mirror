#ifndef OOZE_H_
#define OOZE_H_

enum State = { roaming, eating, attacking, approaching, retreating, dying, inCrack};

int numOozes = 0;

//initialize the HUD
class Ooze
{
private:
    State state;
    int hostility;
    
public:
    void Ooze();
    
    void increaseHostility();
    void decreaseHostility();

};

#endif  //  BANDCAMP_HUD_H_
