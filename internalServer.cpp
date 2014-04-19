#include "internalServer.hpp"
#include "level.hpp"
#include "global.hpp"

internalServerClass::internalServerClass(std::string path)
{
    std::vector<sf::IntRect> rectForPlayerPlace;
    endOfGame = false;
    gameReady = levelClass::loadLevel(path, thisGame.totalPlayer, thisGame.totalMoveForPlayer, thisGame.totalNumberForPlayer, thisGame.totalMoveForNumberForPlayer, rectForPlayerPlace, staticTray);
    if(gameReady == true)
    {
        thisGame.themPlayer.resize(thisGame.totalPlayer);
        for(int i = 0; i < thisGame.totalPlayer; ++i)
        {
            thisGame.themPlayer[i].restMove = thisGame.totalNumberForPlayer;
            thisGame.themPlayer[i].restNumber = thisGame.totalNumberForPlayer;
            thisGame.themPlayer[i].selectedCase = point(-1, -1);
            thisGame.themPlayer[i].restMoveForNumber.resize(thisGame.totalNumberForPlayer);
            for(int j = 0; j < thisGame.totalNumberForPlayer; ++j)
            {
                thisGame.themPlayer[i].restMoveForNumber[j] = thisGame.totalMoveForNumberForPlayer;
            }
            thisGame.themPlayer[i].rectForPlace = rectForPlayerPlace[i];
        }
        thisGame.currentAction.action = PLACE;
        thisGame.currentAction.player = RED;
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
        staticTray.updateWall();
        staticTray.createLine();
        listOfRect.push_back(staticTray.creatRectPlaceFor(RED, thisGame.themPlayer[RED].rectForPlace));
    }
}

void internalServerClass::update()
{
    update(NULL);
}

void internalServerClass::update(sf::Packet* packet)
{
    if(gameReady == false)
    {
        return;
    }

    if(thisGame.currentAction.action == PLAY && thisGame.themPlayer[thisGame.currentAction.player].restMove == 0)
    {
        sf::Lock lock(mutex);
        thisGame.themPlayer[thisGame.currentAction.player].restMove = thisGame.totalMoveForPlayer;
        for(int i = 0; i < thisGame.totalNumberForPlayer; ++i)
        {
            if(thisGame.themPlayer[thisGame.currentAction.player].restMoveForNumber[i] >= 0)
            {
                thisGame.themPlayer[thisGame.currentAction.player].restMoveForNumber[i] = thisGame.totalMoveForNumberForPlayer;
            }
        }
        do
        {
            thisGame.currentAction.player = static_cast<typePlayer>(static_cast<int>(thisGame.currentAction.player) + 1);
            if(thisGame.currentAction.player >= thisGame.totalPlayer)
            {
                thisGame.currentAction.player = static_cast<typePlayer>(0);
            }
            if(thisGame.themPlayer[thisGame.currentAction.player].restNumber != 0)
            {
                checkPlayerCanMove(thisGame.currentAction.player);
            }
        } while(thisGame.themPlayer[thisGame.currentAction.player].restNumber == 0 && thisGame.currentAction.action == PLAY);
        if(packet != NULL)
        {
            *packet << static_cast<sf::Uint8>(CHANGE_ACTION);
            *packet << static_cast<sf::Uint8>(thisGame.currentAction.action);
            *packet << static_cast<sf::Uint8>(thisGame.currentAction.player);
            *packet << false;
        }
    }
    else if(thisGame.currentAction.action == PLACE && thisGame.themPlayer[thisGame.currentAction.player].restMove == 0)
    {
        sf::Lock lock(mutex);
        thisGame.themPlayer[thisGame.currentAction.player].restMove = thisGame.totalMoveForPlayer;
        thisGame.currentAction.player = static_cast<typePlayer>(static_cast<int>(thisGame.currentAction.player) + 1);
        if(thisGame.currentAction.player >= thisGame.totalPlayer)
        {
            listOfRect.clear();
            thisGame.currentAction.player = static_cast<typePlayer>(0);
            thisGame.currentAction.action = PLAY;
            if(packet != NULL)
            {
                *packet << static_cast<sf::Uint8>(CHANGE_ACTION);
                *packet << static_cast<sf::Uint8>(thisGame.currentAction.action);
                *packet << static_cast<sf::Uint8>(thisGame.currentAction.player);
                *packet << true;
                *packet << static_cast<sf::Uint8>(ERASE_RECT);
            }
        }
        else
        {
            listOfRect.clear();
            listOfRect.push_back(staticTray.creatRectPlaceFor(thisGame.currentAction.player, thisGame.themPlayer[thisGame.currentAction.player].rectForPlace));
            if(packet != NULL)
            {
                *packet << static_cast<sf::Uint8>(CHANGE_ACTION);
                *packet << static_cast<sf::Uint8>(thisGame.currentAction.action);
                *packet << static_cast<sf::Uint8>(thisGame.currentAction.player);
                *packet << true;
                *packet << static_cast<sf::Uint8>(RECT_FOR_PLACE) << static_cast<sf::Uint8>(thisGame.currentAction.player);
                *packet << static_cast<sf::Uint8>(thisGame.themPlayer[thisGame.currentAction.player].rectForPlace.left);
                *packet << static_cast<sf::Uint8>(thisGame.themPlayer[thisGame.currentAction.player].rectForPlace.top);
                *packet << static_cast<sf::Uint8>(thisGame.themPlayer[thisGame.currentAction.player].rectForPlace.width);
                *packet << static_cast<sf::Uint8>(thisGame.themPlayer[thisGame.currentAction.player].rectForPlace.height);
            }
        }
    }
    else if(thisGame.currentAction.action == WIN && endOfGame == false)
    {
        if(packet != NULL)
        {
            *packet << static_cast<sf::Uint8>(CHANGE_ACTION);
            *packet << static_cast<sf::Uint8>(thisGame.currentAction.action);
            *packet << static_cast<sf::Uint8>(thisGame.currentAction.player);
            *packet << false;
        }
        endOfGame = true;
    }

    for(auto& caseTray : thisGame.tray)
    {
        caseTray.second.update();
    }
}

typePlayer internalServerClass::getPlayerPlay()
{
    return NO_PLAYER;
}

void internalServerClass::clickTo(int x, int y)
{
    clickTo(x, y, NULL, thisGame.currentAction.player);
}

void internalServerClass::clickTo(int x, int y, sf::Packet* packet, typePlayer forThisPlayer)
{
    if(gameReady == false)
    {
        return;
    }

    if(x >= 0 && x < staticTray.sizeTray.x && y >= 0 && y < staticTray.sizeTray.y)
    {
        std::list<sf::Packet> listPacketToSend;
        sf::Lock lock(mutex);
        if(forThisPlayer != thisGame.currentAction.player)
        {
            return;
        }
        if(thisGame.currentAction.action == PLAY)
        {
            bool isOtherHead = false;
            std::map<point, caseTypeClass>::iterator it = thisGame.tray.find(point(x, y));
            if(it != thisGame.tray.end())
            {
                if(it->second.getPlayer() == thisGame.currentAction.player && it->second.getIsHead() && thisGame.themPlayer[thisGame.currentAction.player].restMoveForNumber[it->second.getNumber()] > 0)
                {
                    std::map<point, caseTypeClass>::iterator secIt = thisGame.tray.find(thisGame.themPlayer[thisGame.currentAction.player].selectedCase);
                    if(secIt != thisGame.tray.end())
                    {
                        secIt->second.setIsSelected(false);
                        if(packet != NULL)
                        {
                            sf::Packet newPacket;
                            newPacket << static_cast<sf::Uint8>(UPDATE_IS_SELECTED);
                            newPacket << secIt->second.getIsSelected();
                            newPacket << static_cast<sf::Uint8>(secIt->first.first);
                            newPacket << static_cast<sf::Uint8>(secIt->first.second);
                            listPacketToSend.push_back(newPacket);
                        }
                    }
                    it->second.setIsSelected(true);
                    if(packet != NULL)
                    {
                        sf::Packet newPacket;
                        newPacket << static_cast<sf::Uint8>(UPDATE_IS_SELECTED);
                        newPacket << it->second.getIsSelected();
                        newPacket << static_cast<sf::Uint8>(it->first.first);
                        newPacket << static_cast<sf::Uint8>(it->first.second);
                        listPacketToSend.push_back(newPacket);
                    }
                    thisGame.themPlayer[thisGame.currentAction.player].selectedCase = point(x, y);
                }
                else if(it->second.getPlayer() != thisGame.currentAction.player && it->second.getIsHead())
                {
                    isOtherHead = true;
                }
            }

            if(it == thisGame.tray.end() || isOtherHead == true)
            {
                if(thisGame.themPlayer[thisGame.currentAction.player].selectedCase != point(-1, -1))
                {
                    std::map<point, caseTypeClass>::iterator secIt = thisGame.tray.find(thisGame.themPlayer[thisGame.currentAction.player].selectedCase);
                    point tmpPoint;
                    tmpPoint.first = x - thisGame.themPlayer[thisGame.currentAction.player].selectedCase.first;
                    tmpPoint.second = y - thisGame.themPlayer[thisGame.currentAction.player].selectedCase.second;
                    if(tmpPoint.first >= -1 && tmpPoint.first <= 1 && tmpPoint.second >= -1 && tmpPoint.second <= 1 && secIt != thisGame.tray.end())
                    {
                        if(moveIsPossible(staticTray.listOfWall, thisGame.themPlayer[thisGame.currentAction.player].selectedCase, tmpPoint) == true)
                        {
                            secIt->second.setIsHead(false);
                            secIt->second.setIsSelected(false);
                            if(packet != NULL)
                            {
                                sf::Packet newPacket;
                                newPacket << static_cast<sf::Uint8>(UPDATE_IS_SELECTED_IS_HEAD);
                                newPacket << secIt->second.getIsSelected();
                                newPacket << secIt->second.getIsHead();
                                newPacket << static_cast<sf::Uint8>(secIt->first.first);
                                newPacket << static_cast<sf::Uint8>(secIt->first.second);
                                listPacketToSend.push_back(newPacket);
                            }
                            if(isOtherHead == true)
                            {
                                typePlayer playerDeath = it->second.getPlayer();
                                int numberDeath = it->second.getNumber();
                                for(std::map<point, caseTypeClass>::iterator thirdIt = thisGame.tray.begin(); thirdIt != thisGame.tray.end(); )
                                {
                                    if(thirdIt->second.getPlayer() == playerDeath && thirdIt->second.getNumber() == numberDeath)
                                    {
                                        if(packet != NULL)
                                        {
                                            sf::Packet newPacket;
                                            newPacket << static_cast<sf::Uint8>(ERASE_CASE);
                                            newPacket << static_cast<sf::Uint8>(thirdIt->first.first);
                                            newPacket << static_cast<sf::Uint8>(thirdIt->first.second);
                                            listPacketToSend.push_back(newPacket);
                                        }
                                        thisGame.tray.erase(thirdIt++);
                                        continue;
                                    }
                                    ++thirdIt;
                                }
                                --thisGame.themPlayer[playerDeath].restNumber;
                                thisGame.themPlayer[playerDeath].restMoveForNumber[numberDeath] = -1;
                                checkPlayerCanMove(playerDeath);
                            }
                            caseTypeClass newCase(thisGame.currentAction.player, true, secIt->second.getNumber(), sf::Vector2f(x, y), staticTray.caseSizeTray, staticTray.bordSize, true);
                            if(packet != NULL)
                            {
                                sf::Packet newPacket;
                                newPacket << static_cast<sf::Uint8>(NEW_CASE);
                                newPacket << static_cast<sf::Uint8>(newCase.getPlayer());
                                newPacket << newCase.getIsHead();
                                newPacket << static_cast<sf::Uint8>(newCase.getNumber());
                                newPacket << newCase.getIsSelected();
                                newPacket << static_cast<sf::Uint8>(x);
                                newPacket << static_cast<sf::Uint8>(y);
                                listPacketToSend.push_back(newPacket);
                            }
                            thisGame.tray[point(x, y)] = std::move(newCase);
                            thisGame.themPlayer[thisGame.currentAction.player].selectedCase = point(x, y);
                            --thisGame.themPlayer[thisGame.currentAction.player].restMove;
                            --thisGame.themPlayer[thisGame.currentAction.player].restMoveForNumber[secIt->second.getNumber()];
                            checkPlayerCanMove(thisGame.currentAction.player);

                            bool checkMove = false;
                            for(int i = 0; i < thisGame.totalNumberForPlayer; ++i)
                            {
                                if(thisGame.themPlayer[thisGame.currentAction.player].restMoveForNumber[i] > 0)
                                {
                                    checkMove = true;
                                    break;
                                }
                            }
                            if(checkMove == false)
                            {
                                thisGame.themPlayer[thisGame.currentAction.player].restMove = 0;
                            }

                            if(thisGame.themPlayer[thisGame.currentAction.player].restMove == 0 || thisGame.themPlayer[thisGame.currentAction.player].restMoveForNumber[secIt->second.getNumber()] == 0)
                            {
                                std::map<point, caseTypeClass>::iterator thirdIt = thisGame.tray.find(thisGame.themPlayer[thisGame.currentAction.player].selectedCase);
                                if(thirdIt != thisGame.tray.end())
                                {
                                    thirdIt->second.setIsSelected(false);
                                    if(packet != NULL)
                                    {
                                        sf::Packet newPacket;
                                        newPacket << static_cast<sf::Uint8>(UPDATE_IS_SELECTED);
                                        newPacket << thirdIt->second.getIsSelected();
                                        newPacket << static_cast<sf::Uint8>(thirdIt->first.first);
                                        newPacket << static_cast<sf::Uint8>(thirdIt->first.second);
                                        listPacketToSend.push_back(newPacket);
                                    }
                                }
                                thisGame.themPlayer[thisGame.currentAction.player].selectedCase = point(-1, -1);
                            }
                        }
                    }
                }
            }
        }
        else if(thisGame.currentAction.action == PLACE)
        {
            if(x >= thisGame.themPlayer[thisGame.currentAction.player].rectForPlace.left && x < (thisGame.themPlayer[thisGame.currentAction.player].rectForPlace.left + thisGame.themPlayer[thisGame.currentAction.player].rectForPlace.width) && y >= thisGame.themPlayer[thisGame.currentAction.player].rectForPlace.top && y < (thisGame.themPlayer[thisGame.currentAction.player].rectForPlace.top + thisGame.themPlayer[thisGame.currentAction.player].rectForPlace.height) && (thisGame.tray.find(point(x, y)) == thisGame.tray.end()))
            {
                caseTypeClass newCase(thisGame.currentAction.player, true, thisGame.totalNumberForPlayer - thisGame.themPlayer[thisGame.currentAction.player].restMove, sf::Vector2f(x, y), staticTray.caseSizeTray, staticTray.bordSize);
                if(packet != NULL)
                {
                    sf::Packet newPacket;
                    newPacket << static_cast<sf::Uint8>(NEW_CASE);
                    newPacket << static_cast<sf::Uint8>(newCase.getPlayer());
                    newPacket << newCase.getIsHead();
                    newPacket << static_cast<sf::Uint8>(newCase.getNumber());
                    newPacket << newCase.getIsSelected();
                    newPacket << static_cast<sf::Uint8>(x);
                    newPacket << static_cast<sf::Uint8>(y);
                    listPacketToSend.push_back(newPacket);
                }
                thisGame.tray[point(x, y)] = std::move(newCase);

                --thisGame.themPlayer[thisGame.currentAction.player].restMove;
            }
        }

        if(packet != NULL && listPacketToSend.empty() == false)
        {
            *packet << static_cast<sf::Uint8>(UPDATE_MAP);
            *packet << static_cast<sf::Uint16>(listPacketToSend.size());
            for(sf::Packet& it : listPacketToSend)
            {
                packet->append(it.getData(), it.getDataSize());
            }
        }
    }
}

bool internalServerClass::moveIsPossible(std::vector<wall> theseWall, point thisPoint, point thisMove)
{
    int tmpMoveX = 0;
    int tmpMoveY = 0;

    if(thisMove.first == 1)
    {
        tmpMoveX = 1;
    }
    if(thisMove.second == 1)
    {
        tmpMoveY = 1;
    }

    for(wall& it : theseWall)
    {
        bool moveX = true;
        bool moveY = true;
        bool moveXY = true;
        if(thisMove.first != 0)
        {
            if(it.firstPoint.x - tmpMoveX == thisPoint.first && it.secondPoint.x - tmpMoveX == thisPoint.first && it.firstPoint.y <= thisPoint.second && it.secondPoint.y > thisPoint.second)
            {
                moveX = false;
                if((it.firstPoint.y < thisPoint.second && thisMove.second == -1) || (it.secondPoint.y - 1 > thisPoint.second && thisMove.second == 1))
                {
                    moveXY = false;
                }
            }
        }

        if(thisMove.second != 0)
        {
            if(it.firstPoint.y - tmpMoveY == thisPoint.second && it.secondPoint.y - tmpMoveY == thisPoint.second && it.firstPoint.x <= thisPoint.first && it.secondPoint.x > thisPoint.first)
            {
                moveY = false;
                if((it.firstPoint.x < thisPoint.first && thisMove.first == -1) || (it.secondPoint.x - 1 > thisPoint.first && thisMove.first == 1))
                {
                    moveXY = false;
                }
            }
        }

        if(thisMove.first != 0 && thisMove.second == 0)
        {
            if(moveX == false)
            {
                return false;
            }
        }
        else if(thisMove.first == 0 && thisMove.second != 0)
        {
            if(moveY == false)
            {
                return false;
            }
        }
        else
        {
            if(((moveX || moveY) && moveXY) == false)
            {
                return false;
            }
        }
    }

    return true;
}

void internalServerClass::checkPlayerCanMove(typePlayer player)
{
    bool thisPlayerCanMove = false;
    int restNumber = thisGame.themPlayer[player].restNumber;
    for(auto& it : thisGame.tray)
    {
        bool canMoving = false;
        if(it.second.getPlayer() == player && it.second.getIsHead() == true)
        {
            --restNumber;
            for(int i = it.first.first - 1; i <= it.first.first + 1; ++i)
            {
                for(int j = it.first.second - 1; j <= it.first.second + 1; ++j)
                {
                    if(i < 0 || i >= staticTray.sizeTray.x || j < 0 || j >= staticTray.sizeTray.y)
                    {
                        continue;
                    }
                    std::map<point, caseTypeClass>::iterator secIt = thisGame.tray.find(point(i, j));
                    if(secIt == thisGame.tray.end())
                    {
                        if(moveIsPossible(staticTray.listOfWall, it.first, point(i - it.first.first, j - it.first.second)) == true)
                        {
                            canMoving = true;
                            break;
                        }
                    }
                    else
                    {
                        if(secIt->second.getPlayer() != player && secIt->second.getIsHead() == true)
                        {
                            if(moveIsPossible(staticTray.listOfWall, it.first, point(i - it.first.first, j - it.first.second)) == true)
                            {
                                canMoving = true;
                                break;
                            }
                        }
                    }
                }
                if(canMoving == true)
                {
                    thisPlayerCanMove = true;
                    break;
                }
            }
            if(canMoving == false)
            {
                thisGame.themPlayer[player].restMoveForNumber[it.second.getNumber()] = 0;
            }
            if(restNumber == 0)
            {
                break;
            }
        }
    }
    if(thisPlayerCanMove == false)
    {
        thisGame.themPlayer[player].restNumber = 0;
        checkWin();
    }
}

void internalServerClass::checkWin()
{
    int numberPlayerNoLost = 0;
    typePlayer thePlayer = thisGame.currentAction.player;
    for(int i = 0; i < thisGame.totalPlayer; ++i)
    {
        if(thisGame.themPlayer[i].restNumber != 0)
        {
            ++numberPlayerNoLost;
            if(numberPlayerNoLost > 1)
            {
                return;
            }
            thePlayer = static_cast<typePlayer>(i);
        }
    }

    thisGame.currentAction.action = WIN;
    thisGame.currentAction.player = thePlayer;
}

int internalServerClass::getTotalPlayer()
{
    return thisGame.totalPlayer;
}

int internalServerClass::getMoveForNumber()
{
    std::map<point, caseTypeClass>::iterator secIt = thisGame.tray.find(thisGame.themPlayer[thisGame.currentAction.player].selectedCase);
    if(secIt != thisGame.tray.end())
    {
        return thisGame.themPlayer[thisGame.currentAction.player].restMoveForNumber[secIt->second.getNumber()];
    }
    else
    {
        return 0;
    }
}

int internalServerClass::getMoveForPlayer()
{
    return thisGame.themPlayer[thisGame.currentAction.player].restMove;
}

sf::Packet internalServerClass::getPacketForMap()
{
    sf::Packet packet;
    packet << static_cast<sf::Uint8>(THE_MAP);
    packet << static_cast<sf::Uint8>(staticTray.listOfWall.size());
    for(wall& it : staticTray.listOfWall)
    {
        packet << static_cast<sf::Uint8>(it.firstPoint.x) << static_cast<sf::Uint8>(it.firstPoint.y) << static_cast<sf::Uint8>(it.secondPoint.x) << static_cast<sf::Uint8>(it.secondPoint.y);
    }
    packet << static_cast<sf::Uint8>(staticTray.sizeTray.x) << static_cast<sf::Uint8>(staticTray.sizeTray.y);

    packet << static_cast<sf::Uint8>(thisGame.currentAction.action);
    packet << static_cast<sf::Uint8>(thisGame.currentAction.player);

    if(thisGame.currentAction.action == PLACE)
    {
        packet << true;
        packet << static_cast<sf::Uint8>(RECT_FOR_PLACE) << static_cast<sf::Uint8>(thisGame.currentAction.player);
        packet << static_cast<sf::Uint8>(thisGame.themPlayer[thisGame.currentAction.player].rectForPlace.left);
        packet << static_cast<sf::Uint8>(thisGame.themPlayer[thisGame.currentAction.player].rectForPlace.top);
        packet << static_cast<sf::Uint8>(thisGame.themPlayer[thisGame.currentAction.player].rectForPlace.width);
        packet << static_cast<sf::Uint8>(thisGame.themPlayer[thisGame.currentAction.player].rectForPlace.height);
    }
    else
    {
        packet << false;
    }

    packet << static_cast<sf::Uint16>(thisGame.tray.size());

    for(auto& thisCase : thisGame.tray)
    {
        packet << static_cast<sf::Uint8>(NEW_CASE);
        packet << static_cast<sf::Uint8>(thisCase.second.getPlayer());
        packet << thisCase.second.getIsHead();
        packet << static_cast<sf::Uint8>(thisCase.second.getNumber());
        packet << thisCase.second.getIsSelected();
        packet << static_cast<sf::Uint8>(thisCase.first.first);
        packet << static_cast<sf::Uint8>(thisCase.first.second);
    }

    return packet;
}

void internalServerClass::playerLeave()
{
    playerLeave(thisGame.currentAction.player);
}

void internalServerClass::playerLeave(typePlayer thisPlayer)
{
    if(thisPlayer != NO_PLAYER && static_cast<int>(thisPlayer) < thisGame.totalPlayer)
    {
        thisGame.themPlayer[thisPlayer].restNumber = 0;
        thisGame.themPlayer[thisPlayer].restMove = -1;
    }
    checkWin();
}

void internalServerClass::startRecord()
{
    return;
}

void internalServerClass::stopRecord()
{
    return;
}
