#include "networkRecorder.hpp"
#include "typeForGame.hpp"

networkRecorderClass::networkRecorderClass(std::list<sf::Packet>* newListOfPacket)
{
    listOfPacket = newListOfPacket;
}

bool networkRecorderClass::onStart()
{
    if(listOfPacket == nullptr)
    {
        return false;
    }
    else
    {
        return true;
    }
}

bool networkRecorderClass::onProcessSamples(const sf::Int16* samples, std::size_t sampleCount)
{
    sf::Packet packet;
    packet << static_cast<sf::Uint8>(TYPE_AUDIO);
    packet << static_cast<sf::Uint8>(AUDIO_STREAM);
    packet.append(samples, sampleCount * sizeof(sf::Int16));
    listOfPacket->push_back(packet);

    return true;
}

void networkRecorderClass::onStop()
{
    sf::Packet packet;
    packet << static_cast<sf::Uint8>(TYPE_AUDIO);
    packet << static_cast<sf::Uint8>(END_OF_AUDIO_STREAM);
    listOfPacket->push_back(packet);
}
