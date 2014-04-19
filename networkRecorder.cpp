#include "networkRecorder.hpp"
#include "typeForGame.hpp"

networkRecorderClass::networkRecorderClass(std::function<void(sf::Packet&)> newSlot)
{
    slot = newSlot;
}

bool networkRecorderClass::onStart()
{
    return true;
}

bool networkRecorderClass::onProcessSamples(const sf::Int16* samples, std::size_t sampleCount)
{
    sf::Packet packet;
    packet << static_cast<sf::Uint8>(TYPE_AUDIO);
    packet << static_cast<sf::Uint8>(AUDIO_STREAM);
    packet.append(samples, sampleCount * sizeof(sf::Int16));
    slot(packet);

    return true;
}

void networkRecorderClass::onStop()
{
    sf::Packet packet;
    packet << static_cast<sf::Uint8>(TYPE_AUDIO);
    packet << static_cast<sf::Uint8>(END_OF_AUDIO_STREAM);
    slot(packet);
}
