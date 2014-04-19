#ifndef EXTERNALSERVER_HPP
#define EXTERNALSERVER_HPP

#include <SFML/Network.hpp>
#include <memory>
#include <list>
#include <condition_variable>
#include <mutex>

#include "server.hpp"
#include "structForGame.hpp"
#include "networkRecorder.hpp"
#include "networkAudioStream.hpp"

#define TIMEOUT 1

class externalServerClass : public serverClass
{
public:
    externalServerClass(std::string ip, int port);
    ~externalServerClass();
    void update();
    typePlayer getPlayerPlay();
    void receivePacket();
    void sendPacket();
    void setMap(sf::Packet& packet);
    void updateMap(sf::Packet& packet);
    void changeAction(sf::Packet& packet);
    void clickTo(int x, int y);
    int getMoveForPlayer();
    int getMoveForNumber();
    void playerLeave();
    void startRecord();
    void stopRecord();
    void playSound(sf::Packet& packet);
    void addNewPacket(sf::Packet& packet);
private:
    bool running;
    bool ready;
    int numberMoveTotal;
    int numberMoveNumber;
    typePlayer playerPlay;
    std::unique_ptr<sf::Thread> receiveThread;
    std::unique_ptr<sf::Thread> sendThread;
    std::list<sf::Packet> listPacket;
    sf::TcpSocket socket;
    sf::SocketSelector selector;
    std::unique_ptr<networkRecorderClass> recorder;
    std::deque<std::unique_ptr<networkAudioStreamClass>> listOfStream;
    std::mutex mutex;
    std::condition_variable condVar;
};

#endif
