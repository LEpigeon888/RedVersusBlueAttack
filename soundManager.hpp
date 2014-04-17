#ifndef SOUNDMANAGER_HPP
#define SOUNDMANAGER_HPP

#include <SFML/Audio.hpp>

class soundManagerClass
{
public:
    void loadSound();
    sf::SoundBuffer soundPlace;
    sf::SoundBuffer endTurn;
    sf::SoundBuffer yourTurn;
};

#endif
