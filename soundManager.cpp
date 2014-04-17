#include "soundManager.hpp"

void soundManagerClass::loadSound()
{
    soundPlace.loadFromFile("soundPlace.ogg");
    endTurn.loadFromFile("endTurn.ogg");
    yourTurn.loadFromFile("yourTurn.ogg");
}
