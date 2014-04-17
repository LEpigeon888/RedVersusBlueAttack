#ifndef PLAYSTATE_HPP
#define PLAYSTATE_HPP

#include <memory>

#include "gameState.hpp"
#include "server.hpp"
#include "widgetManager.hpp"
#include "soundManager.hpp"

class textWidgetClass;

class playStateClass : public gameStateClass
{
public:
    playStateClass(serverClass* newServer);
    ~playStateClass();
    void update();
    void draw();
    void printAction();
    void printPlayer();
    std::string intToStr(int thisInt);
private:
    std::unique_ptr<serverClass> server;
    action currentAction;
    typePlayer playerPlay;
    int numberMoveTotal;
    int numberMoveNumber;
    sf::Sound soundForEndTurn;
    sf::Sound soundForYourTurn;
    widgetManagerClass myWidgetManager;
    textWidgetClass* actionType;
    textWidgetClass* actionPlayer;
    textWidgetClass* moveTotal;
    textWidgetClass* moveNumber;
    textWidgetClass* namePlayerPlay;
};

#endif
