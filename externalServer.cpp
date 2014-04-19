#include "externalServer.hpp"
#include "global.hpp"

externalServerClass::externalServerClass(std::string ip, int port)
{
    running = true;
    ready = false;
    numberMoveTotal = 0;
    numberMoveNumber = 0;
    thisGame.currentAction.action = NOT_SET;
    thisGame.currentAction.player = RED;
    playerPlay = NO_PLAYER;
    listOfStream.resize(4);
    socket.setBlocking(true);
    if(socket.connect(ip, port) != sf::Socket::Status::Done)
    {
        gameReady = false;
    }
    else
    {
        gameReady = true;
    }
    socket.setBlocking(false);
    selector.add(socket);
    receiveThread.reset(new sf::Thread(&externalServerClass::receivePacket, this));
    sendThread.reset(new sf::Thread(&externalServerClass::sendPacket, this));
    receiveThread->launch();
    sendThread->launch();
}

externalServerClass::~externalServerClass()
{
    running = false;
    receiveThread->wait();
    sendThread->wait();
}

void externalServerClass::update()
{
    for(auto& caseTray : thisGame.tray)
    {
        caseTray.second.update();
    }
}

typePlayer externalServerClass::getPlayerPlay()
{
    return playerPlay;
}

void externalServerClass::receivePacket()
{
    while(running)
    {
        if(selector.wait(sf::seconds(TIMEOUT)))
        {
            if(selector.isReady(socket))
            {
                sf::Packet packet;
                sf::Socket::Status stat = socket.receive(packet);
                if(stat == sf::Socket::Status::Done)
                {
                    sf::Uint8 tmpType;
                    packet >> tmpType;
                    if(tmpType == THE_MAP)
                    {
                        setMap(packet);
                    }
                    else if(tmpType == UPDATE_MAP)
                    {
                        updateMap(packet);
                    }
                    else if(tmpType == CHANGE_ACTION)
                    {
                        changeAction(packet);
                    }
                    else if(tmpType == YOU_ARE)
                    {
                        sf::Uint8 thisPlayer;
                        packet >> thisPlayer;

                        playerPlay = static_cast<typePlayer>(thisPlayer);
                    }
                    else if(tmpType == SET_MOVE_TOTAL)
                    {
                        sf::Uint8 number;
                        packet >> number;

                        numberMoveTotal = number;
                    }
                    else if(tmpType == SET_MOVE_NUMBER)
                    {
                        sf::Uint8 number;
                        packet >> number;

                        numberMoveNumber = number;
                    }
                    else if(tmpType == TYPE_AUDIO)
                    {
                        playSound(packet);
                    }
                }
                else
                {
                    gameReady = false;
                }
            }
        }
    }
}

void externalServerClass::sendPacket()
{
    while(running)
    {
        while(listPacket.empty() == true && running == true)
        {
            std::unique_lock<std::mutex> lock(mutex);
            condVar.wait_for(lock, std::chrono::seconds(TIMEOUT));
        }
        if(listPacket.empty() == false)
        {
            sf::Socket::Status stat = socket.send(listPacket.front());
            if(stat == sf::Socket::Status::Done)
            {
                listPacket.pop_front();
            }
            else if(stat != sf::Socket::Status::NotReady)
            {
                gameReady = false;
            }
        }
    }
}

void externalServerClass::setMap(sf::Packet& packet)
{
    sf::Uint8 sizeWall;
    sf::Uint8 sizeTrayX;
    sf::Uint8 sizeTrayY;

    packet >> sizeWall;
    staticTray.listOfWall.clear();
    for(int i = 0; i < sizeWall; ++i)
    {
        sf::Uint8 firstX;
        sf::Uint8 firstY;
        sf::Uint8 secondX;
        sf::Uint8 secondY;

        packet >> firstX >> firstY >> secondX >> secondY;

        staticTray.addNewWall(sf::Vector2f(firstX, firstY), sf::Vector2f(secondX, secondY));
    }

    packet >> sizeTrayX;
    packet >> sizeTrayY;
    staticTray.sizeTray.x = sizeTrayX;
    staticTray.sizeTray.y = sizeTrayY;
    staticTray.caseSizeTray = sf::Vector2f(global::window.getSize().x / 2 / staticTray.sizeTray.x, global::window.getSize().y / staticTray.sizeTray.y);
    staticTray.bordSize = sf::Vector2f(0,0);
    if(staticTray.caseSizeTray.x > staticTray.caseSizeTray.y)
    {
        staticTray.bordSize.x = (staticTray.caseSizeTray.x - staticTray.caseSizeTray.y) * staticTray.sizeTray.x / 2;
        staticTray.caseSizeTray.x = staticTray.caseSizeTray.y;
    }
    else if(staticTray.caseSizeTray.x < staticTray.caseSizeTray.y)
    {
        staticTray.bordSize.y = (staticTray.caseSizeTray.y - staticTray.caseSizeTray.x) * staticTray.sizeTray.y / 2;
        staticTray.caseSizeTray.y = staticTray.caseSizeTray.x;
    }

    changeAction(packet);

    updateMap(packet);

    staticTray.updateWall();
    staticTray.createLine();

    ready = true;
}

void externalServerClass::updateMap(sf::Packet& packet)
{
    sf::Uint16 sizeList;
    packet >> sizeList;

    for(int i = 0; i < sizeList; ++i)
    {
        sf::Uint8 typeUpdate;
        packet >> typeUpdate;

        if(static_cast<typeSend>(typeUpdate) == NEW_CASE)
        {
            sf::Uint8 thePlayer;
            bool isHead;
            sf::Uint8 theNumber;
            bool isSelected;
            sf::Uint8 xPos;
            sf::Uint8 yPos;

            packet >> thePlayer >> isHead >> theNumber >> isSelected >> xPos >> yPos;

            thisGame.tray[point(xPos, yPos)] = std::move(caseTypeClass(static_cast<typePlayer>(thePlayer), isHead, theNumber, sf::Vector2f(xPos, yPos), staticTray.caseSizeTray, staticTray.bordSize, isSelected));
        }
        else if(static_cast<typeSend>(typeUpdate) == ERASE_CASE)
        {
            sf::Uint8 xPos;
            sf::Uint8 yPos;

            packet >> xPos >> yPos;

            thisGame.tray.erase(point(xPos, yPos));
        }
        else if(static_cast<typeSend>(typeUpdate) == UPDATE_IS_SELECTED)
        {
            bool isSelected;
            sf::Uint8 xPos;
            sf::Uint8 yPos;

            packet >> isSelected >> xPos >> yPos;

            std::map<point, caseTypeClass>::iterator ite = thisGame.tray.find(point(xPos, yPos));
            if(ite != thisGame.tray.end())
            {
                ite->second.setIsSelected(isSelected);
            }
        }
        else if(static_cast<typeSend>(typeUpdate) == UPDATE_IS_SELECTED_IS_HEAD)
        {
            bool isSelected;
            bool isHead;
            sf::Uint8 xPos;
            sf::Uint8 yPos;

            packet >> isSelected >> isHead >> xPos >> yPos;

            std::map<point, caseTypeClass>::iterator ite = thisGame.tray.find(point(xPos, yPos));
            if(ite != thisGame.tray.end())
            {
                ite->second.setIsSelected(isSelected);
                ite->second.setIsHead(isHead);
            }
        }
    }
}

void externalServerClass::changeAction(sf::Packet& packet)
{
    sf::Uint8 currentAction;
    sf::Uint8 currentPlayer;
    bool containRect;

    packet >> currentAction >> currentPlayer;
    thisGame.currentAction.action = static_cast<typeAction>(currentAction);
    thisGame.currentAction.player = static_cast<typePlayer>(currentPlayer);

    packet >> containRect;
    if(containRect == true)
    {
        sf::Uint8 typeRect;
        packet >> typeRect;

        if(static_cast<typeSend>(typeRect) == ERASE_RECT)
        {
            listOfRect.clear();
        }
        else if(static_cast<typeSend>(typeRect) == RECT_FOR_PLACE)
        {
            sf::Uint8 thePlayer;
            sf::Uint8 left;
            sf::Uint8 top;
            sf::Uint8 width;
            sf::Uint8 height;

            packet >> thePlayer >> left >> top >> width >> height;

            listOfRect.clear();
            listOfRect.push_back(staticTray.creatRectPlaceFor(static_cast<typePlayer>(thePlayer), sf::IntRect(left, top, width, height)));
        }
    }
}

void externalServerClass::clickTo(int x, int y)
{
    sf::Packet packet;
    packet << static_cast<sf::Uint8>(CLICK_TO);
    packet << static_cast<sf::Uint8>(x);
    packet << static_cast<sf::Uint8>(y);
    addNewPacket(packet);
}

int externalServerClass::getMoveForPlayer()
{
    return numberMoveTotal;
}

int externalServerClass::getMoveForNumber()
{
    return numberMoveNumber;
}

void externalServerClass::playerLeave()
{
    sf::Packet packet;
    packet << static_cast<sf::Uint8>(I_BELIEVE_I_CAN_LEAVE);
    addNewPacket(packet);
}

void externalServerClass::startRecord()
{
    if(recorder.get() == nullptr)
    {
        recorder.reset(new networkRecorderClass(std::bind(&externalServerClass::addNewPacket, this, std::placeholders::_1)));
        recorder->start();
    }
}

void externalServerClass::stopRecord()
{
    if(recorder.get() != nullptr)
    {
        recorder->stop();
        recorder.reset();
    }
}

void externalServerClass::playSound(sf::Packet& packet)
{
    typePlayer player;
    sf::Uint8 thePlayer;
    packet >> thePlayer;
    player = static_cast<typePlayer>(thePlayer);

    if(listOfStream[player].get() != nullptr)
    {
        if(listOfStream[player]->getStatus() == sf::SoundStream::Stopped)
        {
            listOfStream[player].reset();
        }
    }

    if(listOfStream[player].get() == nullptr)
    {
        listOfStream[player].reset(new networkAudioStreamClass);
        listOfStream[player]->start();
    }

    listOfStream[player]->addNewPacket(packet);
}

void externalServerClass::addNewPacket(sf::Packet& packet)
{
    std::unique_lock<std::mutex> lock(mutex);
    listPacket.push_back(packet);
    condVar.notify_one();
}
