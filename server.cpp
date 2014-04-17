#include "server.hpp"

void serverClass::draw()
{
    for(auto& it : thisGame.tray)
    {
        global::window.draw(it.second.sprite());
    }
    staticTray.draw();
    for(sf::RectangleShape& it : listOfRect)
    {
        global::window.draw(it);
    }
}

sf::Vector2f serverClass::getBordSize()
{
    return staticTray.bordSize;
}

sf::Vector2f serverClass::getCaseSizeTray()
{
    return staticTray.caseSizeTray;
}

action serverClass::getCurrentAction()
{
    return thisGame.currentAction;
}

bool serverClass::getGameReady()
{
    return gameReady;
}
