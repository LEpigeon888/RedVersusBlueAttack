#include <sstream>

#include "serverState.hpp"
#include "global.hpp"
#include "level.hpp"
#include "mainMenuState.hpp"
#include "textWidget.hpp"
#include <iostream>
serverStateClass::serverStateClass(int numPort, std::string pathToLevel) : server(pathToLevel)
{
    widgetClass* listForType;
    widgetClass* listForPlayer;
    widgetClass* listForNbPlayer;
    widgetClass* listForNbSpec;
    widgetClass* listForNb;
    widgetClass* listForAction;

    currentAction.action = NOT_SET;
    currentAction.player = RED;
    running = true;
    playerReady = false;
    numberOfPlayer = 0;
    numberOfSpectator = 0;
    numberMoveTotal = 0;
    numberMoveNumber = 0;
    currentTypeSound = global::soundType;
    global::soundType = NEVER;

    myWidgetManager.setLimit(sf::IntRect(global::window.getSize().x / 2, 0, global::window.getSize().x / 2, global::window.getSize().y));
    actionType = new textWidgetClass("NONE");
    actionPlayer = new textWidgetClass("NONE");
    nbPlayer = new textWidgetClass("0");
    nbSpec = new textWidgetClass("0");

    myWidgetManager.addToTmpList(new textWidgetClass("Joueur : "));
    myWidgetManager.addToTmpList(nbPlayer);
    listForNbPlayer = myWidgetManager.createList(HORIZONTAL, MIDDLE, 5);

    myWidgetManager.addToTmpList(new textWidgetClass("Spectateur : "));
    myWidgetManager.addToTmpList(nbSpec);
    listForNbSpec = myWidgetManager.createList(HORIZONTAL, MIDDLE, 5);

    myWidgetManager.addToTmpList(new textWidgetClass("Nombre de :"));
    myWidgetManager.addToTmpList(listForNbPlayer);
    myWidgetManager.addToTmpList(listForNbSpec);
    listForNb = myWidgetManager.createList(VERTICAL, MIDDLE, 8);

    myWidgetManager.addToTmpList(new textWidgetClass("Type : "));
    myWidgetManager.addToTmpList(actionType);
    listForType = myWidgetManager.createList(HORIZONTAL, MIDDLE, 5);

    myWidgetManager.addToTmpList(new textWidgetClass("Joueur : "));
    myWidgetManager.addToTmpList(actionPlayer);
    listForPlayer = myWidgetManager.createList(HORIZONTAL, MIDDLE, 6);

    myWidgetManager.addToTmpList(new textWidgetClass("Action :"));
    myWidgetManager.addToTmpList(listForType);
    myWidgetManager.addToTmpList(listForPlayer);
    listForAction = myWidgetManager.createList(VERTICAL, MIDDLE, 8);

    myWidgetManager.addToTmpList(listForNb);
    myWidgetManager.addToTmpList(listForAction);
    myWidgetManager.setWidgetHere(myWidgetManager.createList(VERTICAL, MIDDLE, 125), MIDDLE_MIDDLE);

    listener.setBlocking(false);
    if(server.getGameReady() == true)
    {
        playerIsReady.resize(server.getTotalPlayer(), false);
        listener.listen(numPort);
        sendPacketThread.reset(new sf::Thread(&serverStateClass::sendPacket, this));
        receivePacketThread.reset(new sf::Thread(&serverStateClass::receivePacket, this));
        sendPacketThread->launch();
        receivePacketThread->launch();
    }
}

serverStateClass::~serverStateClass()
{
    global::soundType = currentTypeSound;
    running = false;
    if(sendPacketThread.get() != nullptr)
    {
        sendPacketThread->wait();
    }
    if(receivePacketThread.get() != nullptr)
    {
        receivePacketThread->wait();
    }
}

void serverStateClass::update()
{
    int tmpNumber;

    sf::Event event;
    while(global::window.pollEvent(event))
    {
        if(event.type == sf::Event::Closed)
        {
            global::run = false;
        }
        else if(event.type == sf::Event::KeyPressed)
        {
            if(event.key.code == sf::Keyboard::Escape)
            {
                global::gameStateStack.set(new mainMenuStateClass);
                return;
            }
        }
    }

    if(server.getGameReady() == false)
    {
        global::gameStateStack.set(new mainMenuStateClass);
        return;
    }

    myWidgetManager.update();

    if(playerReady == true)
    {
        action tmpAction;
        sf::Packet newPacket;
        server.update(&newPacket);
        tmpAction = server.getCurrentAction();
        if(currentAction.action != tmpAction.action || currentAction.player != tmpAction.player)
        {
            currentAction = tmpAction;
            printAction();
        }

        if(newPacket.getDataSize() != 0)
        {
            sendToAll(newPacket);
        }
    }

    waitConnection();

    for(std::list<std::shared_ptr<client>>::iterator ite = listClientMainThread.begin(); ite != listClientMainThread.end(); )
    {
        if((*ite)->isConnected == false)
        {
            if((*ite)->player != NO_PLAYER)
            {
                playerIsReady[(*ite)->player] = false;
                playerReady = false;
                --numberOfPlayer;
            }
            else
            {
                --numberOfSpectator;
            }

            nbPlayer->setMessage(intToStr(numberOfPlayer));
            nbSpec->setMessage(intToStr(numberOfSpectator));
            myWidgetManager.widgetHasChanged();

            selector.remove((*ite)->socket);
            listClientMainThread.erase(ite++);
            continue;
        }
        ++ite;
    }

    tmpNumber = server.getMoveForPlayer();
    if(tmpNumber != numberMoveTotal)
    {
        sf::Packet packet;
        numberMoveTotal = tmpNumber;
        packet << static_cast<sf::Uint8>(SET_MOVE_TOTAL);
        packet << static_cast<sf::Uint8>(numberMoveTotal);
        sendToAll(packet);
    }
    tmpNumber = server.getMoveForNumber();
    if(tmpNumber != numberMoveNumber)
    {
        sf::Packet packet;
        numberMoveNumber = tmpNumber;
        packet << static_cast<sf::Uint8>(SET_MOVE_NUMBER);
        packet << static_cast<sf::Uint8>(numberMoveNumber);
        sendToAll(packet);
    }
}

void serverStateClass::draw()
{
    global::window.clear(sf::Color::White);
    server.draw();
    myWidgetManager.draw();
}

void serverStateClass::printAction()
{
    if(currentAction.action == NOT_SET)
    {
        actionType->setMessage("NOT_SET");
    }
    else if(currentAction.action == PLAY)
    {
        actionType->setMessage("jouer");
    }
    else if(currentAction.action == PLACE)
    {
        actionType->setMessage("placer");
    }
    else if(currentAction.action == WIN)
    {
        actionType->setMessage("gagner");
    }

    if(currentAction.player == RED)
    {
        actionPlayer->setMessage("rouge");
    }
    else if(currentAction.player == BLUE)
    {
        actionPlayer->setMessage("bleu");
    }
    else if(currentAction.player == MAGENTA)
    {
        actionPlayer->setMessage("magenta");
    }
    else if(currentAction.player == CYAN)
    {
        actionPlayer->setMessage("cyan");
    }

    myWidgetManager.widgetHasChanged();
}

void serverStateClass::playerClickedTo(sf::Packet& packet, typePlayer thisPlayer)
{
    sf::Packet newPacket;
    sf::Uint8 x;
    sf::Uint8 y;
    packet >> x >> y;

    server.clickTo(x, y, &newPacket, thisPlayer);

    if(newPacket.getDataSize() != 0)
    {
        sendToAll(newPacket);
    }
}

void serverStateClass::sendToAll(sf::Packet& packet)
{
    for(std::shared_ptr<client>& ite : listClientMainThread)
    {
        ite->listPacket.push_back(packet);
    }
}

void serverStateClass::waitConnection()
{
    std::unique_ptr<client> newClient(new client);
    sf::Socket::Status stat = listener.accept(newClient->socket);
    if(stat == sf::Socket::Done)
    {
        sf::Packet packet;
        sf::Packet packetMoveTotal;
        sf::Packet packetMoveNumber;
        packet << static_cast<sf::Uint8>(YOU_ARE);
        newClient->socket.setBlocking(false);
        selector.add(newClient->socket);
        newClient->player = NO_PLAYER;
        playerReady = true;
        ++numberOfSpectator;
        for(int i = 0; i < server.getTotalPlayer(); ++i)
        {
            if(playerIsReady[i] == false)
            {
                if(newClient->player == NO_PLAYER)
                {
                    playerIsReady[i] = true;
                    newClient->player = static_cast<typePlayer>(i);
                    --numberOfSpectator;
                    ++numberOfPlayer;
                }
                else
                {
                    playerReady = false;
                }
            }
        }

        packetMoveTotal << static_cast<sf::Uint8>(SET_MOVE_TOTAL);
        packetMoveTotal << static_cast<sf::Uint8>(numberMoveTotal);
        packetMoveNumber << static_cast<sf::Uint8>(SET_MOVE_NUMBER);
        packetMoveNumber << static_cast<sf::Uint8>(numberMoveNumber);

        nbPlayer->setMessage(intToStr(numberOfPlayer));
        nbSpec->setMessage(intToStr(numberOfSpectator));
        myWidgetManager.widgetHasChanged();

        packet << static_cast<sf::Uint8>(newClient->player);
        listClientMainThread.push_back(std::make_shared<client>());
        listClientMainThread.back().reset(newClient.release());
        listClientSendThread.push_back(listClientMainThread.back());
        listClientReceiveThread.push_back(listClientMainThread.back());
        listClientMainThread.back()->listPacket.push_back(packet);
        listClientMainThread.back()->listPacket.push_back(server.getPacketForMap());
        listClientMainThread.back()->listPacket.push_back(packetMoveTotal);
        listClientMainThread.back()->listPacket.push_back(packetMoveNumber);
    }
}

void serverStateClass::sendPacket()
{
    bool sendThisLoop = false;
    while(running == true)
    {
        for(std::list<std::shared_ptr<client>>::iterator ite = listClientSendThread.begin(); ite != listClientSendThread.end(); )
        {
            if((*ite)->listPacket.empty() == false)
            {
                sendThisLoop = true;
                sf::Socket::Status stat = (*ite)->socket.send((*ite)->listPacket.front());
                if(stat == sf::Socket::Status::Done)
                {
                    (*ite)->listPacket.pop_front();
                }
                else if(stat != sf::Socket::Status::NotReady)
                {
                    (*ite)->isConnected = false;
                }
            }
            if((*ite)->isConnected == false)
            {
                listClientSendThread.erase(ite++);
                continue;
            }
            ++ite;
        }
        if(sendThisLoop == false)
        {
            sf::sleep(sf::seconds(TIME_SLEEP));
        }
        sendThisLoop = false;
    }
}

void serverStateClass::receivePacket()
{
    while(running == true)
    {
        if(selector.wait(sf::seconds(TIMEOUT)))
        {
            for(std::list<std::shared_ptr<client>>::iterator ite = listClientReceiveThread.begin(); ite != listClientReceiveThread.end(); )
            {
                if(selector.isReady((*ite)->socket))
                {
                    sf::Packet packet;
                    sf::Socket::Status stat = (*ite)->socket.receive(packet);
                    if(stat == sf::Socket::Status::Done)
                    {
                        sf::Uint8 tmpType;
                        packet >> tmpType;
                        if(tmpType == CLICK_TO)
                        {
                            if(playerReady == true && (*ite)->player == server.getCurrentAction().player)
                            {
                                playerClickedTo(packet, (*ite)->player);
                            }
                        }
                        else if(tmpType == I_BELIEVE_I_CAN_LEAVE)
                        {
                            server.playerLeave((*ite)->player);
                        }
                    }
                    else if(stat != sf::Socket::Status::NotReady)
                    {
                        (*ite)->isConnected = false;
                    }
                    if((*ite)->isConnected == false)
                    {
                        listClientReceiveThread.erase(ite++);
                        continue;
                    }
                }
                ++ite;
            }
        }
    }
}

std::string serverStateClass::intToStr(int thisInt)
{
    std::ostringstream oss;
    oss << thisInt;
    return oss.str();
}
