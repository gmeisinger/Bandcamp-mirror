#ifndef OOZE_H_
#define OOZE_H_

enum State { roaming, eating, attacking, approaching, retreating, dying, inCrack};

int numOozes = 0;

//
class Ooze
{
private:
    State state;
    int hostility;
    
public:
    Ooze();
    Ooze(State state, int hostility);
    
    void increaseHostility();
    void decreaseHostility();

    ~Ooze();
};

#endif  //  OOZE_H_
