#ifndef SERVERSTATE_HPP
#define SERVERSTATE_HPP

#include <SFML/Network.hpp>
#include <memory>
#include <list>
#include <condition_variable>
#include <mutex>

#include "gameState.hpp"
#include "internalServer.hpp"
#include "structForGame.hpp"
#include "widgetManager.hpp"

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
    void sendAudioForAllExcept(typePlayer thisPlayer, sf::Packet& packet);
    void addNewPacket(sf::Packet& packet, client& thisClient);
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
    std::mutex mutex;
    std::condition_variable condVar;
    bool newPacketAreAvailable;
};

#endif
