#ifndef NETWORKRECORDER_HPP
#define NETWORKRECORDER_HPP

#include <list>
#include <functional>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

class networkRecorderClass : public sf::SoundRecorder
{
public:
    networkRecorderClass(std::function<void(sf::Packet&)> newSlot);
private:
    bool onStart();
    bool onProcessSamples(const sf::Int16* samples, std::size_t sampleCount);
    void onStop();
    std::function<void(sf::Packet&)> slot;
};

#endif
