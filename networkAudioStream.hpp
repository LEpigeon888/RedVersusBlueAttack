#ifndef NETWORKAUDIOSTREAM_HPP
#define NETWORKAUDIOSTREAM_HPP

#include <condition_variable>
#include <mutex>
#include <list>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#define TIME_OUT 1

class networkAudioStreamClass : public sf::SoundStream
{
public:
    networkAudioStreamClass();
    void start();
    void addNewPacket(sf::Packet& packet);
private:
    bool onGetData(sf::SoundStream::Chunk& data);
    void onSeek(sf::Time timeOffset);
    void receiveLoop();
    sf::Mutex mutex;
    std::vector<sf::Int16> samples;
    std::vector<sf::Int16> tempBuffer;
    std::size_t offset;
    bool hasFinished;
    std::list<sf::Packet> listOfPacket;
    std::mutex stdMutex;
    std::condition_variable condVar;
};

#endif
