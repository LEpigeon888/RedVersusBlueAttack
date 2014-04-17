#ifndef NETWORKRECORDER_HPP
#define NETWORKRECORDER_HPP

#include <list>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

class networkRecorderClass : public sf::SoundRecorder
{
public:
    networkRecorderClass(std::list<sf::Packet>* newListOfPacket);
private:
    bool onStart();
    bool onProcessSamples(const sf::Int16* samples, std::size_t sampleCount);
    void onStop();
    std::list<sf::Packet>* listOfPacket;
};

#endif
