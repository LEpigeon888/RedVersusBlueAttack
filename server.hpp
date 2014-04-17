#ifndef SERVER_HPP
#define SERVER_HPP

#include <SFML/Graphics.hpp>

#include "structForGame.hpp"
#include "staticTray.hpp"
#include "global.hpp"

class serverClass
{
public:
    virtual ~serverClass() {}
    virtual void update() = 0;
    virtual void draw();
    virtual sf::Vector2f getBordSize();
    virtual sf::Vector2f getCaseSizeTray();
    virtual action getCurrentAction();
    virtual bool getGameReady();
    virtual typePlayer getPlayerPlay() = 0;
    virtual void clickTo(int x, int y) = 0;
    virtual int getMoveForPlayer() = 0;
    virtual int getMoveForNumber() = 0;
    virtual void playerLeave() = 0;
protected:
    theGame thisGame;
    staticTrayClass staticTray;
    std::vector<sf::RectangleShape> listOfRect;
    bool gameReady;
};

#endif
