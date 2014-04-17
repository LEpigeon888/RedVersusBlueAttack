#ifndef EXTERNALSERVER_HPP
#define EXTERNALSERVER_HPP

#include <SFML/Network.hpp>
#include <memory>
#include <list>

#include "server.hpp"
#include "structForGame.hpp"

#define TIME_SLEEP 0.05
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
};

#endif
