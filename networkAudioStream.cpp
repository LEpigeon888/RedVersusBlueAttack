#include <chrono>

#include "networkAudioStream.hpp"
#include "typeForGame.hpp"

networkAudioStreamClass::networkAudioStreamClass()
{
    offset = 0;
    hasFinished = false;
    initialize(1, 44100);
}

networkAudioStreamClass::~networkAudioStreamClass()
{
    hasFinished = false;
    condVar.notify_one();
    if(threadForReceiveLoop.joinable() == true)
    {
        threadForReceiveLoop.join();
    }
}

void networkAudioStreamClass::start()
{
    if(hasFinished == false)
    {
        play();
        threadForReceiveLoop = std::thread(&networkAudioStreamClass::receiveLoop, this);
    }
    else
    {
        play();
    }
}

void networkAudioStreamClass::addNewPacket(sf::Packet& packet)
{
    std::unique_lock<std::mutex> lock(stdMutex);
    listOfPacket.push_back(packet);
    condVar.notify_one();
}

bool networkAudioStreamClass::onGetData(sf::SoundStream::Chunk& data)
{
    if((offset >= samples.size()) && hasFinished == true)
    {
        return false;
    }

    while((offset >= samples.size()) && hasFinished == false)
    {
        sf::sleep(sf::milliseconds(10));
    }

    {
        sf::Lock lock(mutex);
        tempBuffer.assign(samples.begin() + offset, samples.end());
    }

    data.samples = &tempBuffer[0];
    data.sampleCount = tempBuffer.size();

    offset += tempBuffer.size();

    return true;
}

void networkAudioStreamClass::onSeek(sf::Time timeOffset)
{
    offset = timeOffset.asMilliseconds() * getSampleRate() * getChannelCount() / 1000;
}

void networkAudioStreamClass::receiveLoop()
{
    while(hasFinished == false)
    {
        while(listOfPacket.empty() == true && hasFinished == false)
        {
            std::unique_lock<std::mutex> lock(stdMutex);
            condVar.wait_for(lock, std::chrono::seconds(TIME_OUT));
        }

        if(listOfPacket.empty() == false)
        {
            sf::Uint8 sendType;
            typeSend theType;

            listOfPacket.back() >> sendType;
            theType = static_cast<typeSend>(sendType);

            if(theType == AUDIO_STREAM)
            {
                const sf::Int16* newSamples = reinterpret_cast<const sf::Int16*>(static_cast<const char*>(listOfPacket.back().getData()) + 3);
                std::size_t sampleCount = (listOfPacket.back().getDataSize() - 3) / sizeof(sf::Int16);

                {
                    sf::Lock lock(mutex);
                    std::copy(newSamples, newSamples + sampleCount, std::back_inserter(samples));
                }
            }
            else
            {
                hasFinished = true;
            }
        }
    }
}
