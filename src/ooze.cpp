#include "include/ooze.h"

// Default Constructor
Ooze::Ooze()
    :state{roaming}, hostility{0} {}

//Constructor
Ooze::Ooze(State state, int hostility)
    :state{state}, hostility{hostility} {}


void Ooze::increaseHostility()
{
    hostility++;
}

void Ooze::decreaseHostility()
{
    hostility--;
}
