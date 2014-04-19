#ifndef INTERNALSERVER_HPP
#define INTERNALSERVER_HPP

#include <SFML/Network.hpp>

#include "server.hpp"
#include "structForGame.hpp"

class internalServerClass : public serverClass
{
public:
    internalServerClass(std::string path);
    void update();
    void update(sf::Packet* packet);
    typePlayer getPlayerPlay();
    void clickTo(int x, int y);
    void clickTo(int x, int y, sf::Packet* packet, typePlayer forThisPlayer);
    bool moveIsPossible(std::vector<wall> theseWall, point thisPoint, point thisMove);
    void checkPlayerCanMove(typePlayer player);
    void checkWin();
    int getTotalPlayer();
    int getMoveForPlayer();
    int getMoveForNumber();
    sf::Packet getPacketForMap();
    void playerLeave();
    void playerLeave(typePlayer thisPlayer);
    void startRecord();
    void stopRecord();
public:
    bool endOfGame;
    sf::Mutex mutex;
};

#endif
