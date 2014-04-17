#ifndef SERVERSTATE_HPP
#define SERVERSTATE_HPP

#include <SFML/Network.hpp>
#include <memory>
#include <list>

#include "gameState.hpp"
#include "internalServer.hpp"
#include "structForGame.hpp"
#include "widgetManager.hpp"

#define TIME_SLEEP 0.05
#define TIMEOUT 1

class textWidgetClass;

struct client
{
    bool isConnected = true;
    std::list<sf::Packet> listPacket;
    sf::TcpSocket socket;
    typePlayer player;
};

class serverStateClass : public gameStateClass
{
public:
    serverStateClass(int numPort, std::string pathToLevel);
    ~serverStateClass();
    void update();
    void draw();
    void printAction();
    void playerClickedTo(sf::Packet& packet, typePlayer thisPlayer);
    void sendToAll(sf::Packet& packet);
    void waitConnection();
    void sendPacket();
    void receivePacket();
    std::string intToStr(int thisInt);
private:
    sf::TcpListener listener;
    std::unique_ptr<sf::Thread> sendPacketThread;
    std::unique_ptr<sf::Thread> receivePacketThread;
    std::list<std::shared_ptr<client>> listClientMainThread;
    std::list<std::shared_ptr<client>> listClientSendThread;
    std::list<std::shared_ptr<client>> listClientReceiveThread;
    sf::SocketSelector selector;
    internalServerClass server;
    std::deque<bool> playerIsReady;
    bool running;
    bool playerReady;
    int numberOfPlayer;
    int numberOfSpectator;
    int numberMoveTotal;
    int numberMoveNumber;
    action currentAction;
    typePlayer playerPlay;
    typeSound currentTypeSound;
    widgetManagerClass myWidgetManager;
    textWidgetClass* actionType;
    textWidgetClass* actionPlayer;
    textWidgetClass* nbPlayer;
    textWidgetClass* nbSpec;
};

#endif
