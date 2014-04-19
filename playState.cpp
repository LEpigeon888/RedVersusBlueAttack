#include <sstream>

#include "playState.hpp"
#include "structForGame.hpp"
#include "mainMenuState.hpp"
#include "buttonWidget.hpp"
#include "global.hpp"

playStateClass::playStateClass(serverClass* newServer)
{
    widgetClass* listForType;
    widgetClass* listForPlayer;
    widgetClass* listForMoveTotal;
    widgetClass* listForMoveNumber;
    widgetClass* listForAction;
    widgetClass* listForMove;

    currentAction.action = NOT_SET;
    currentAction.player = RED;
    playerPlay = NO_PLAYER;
    numberMoveTotal = 0;
    numberMoveNumber = 0;
    soundForEndTurn.setBuffer(global::soundManager->endTurn);
    soundForYourTurn.setBuffer(global::soundManager->yourTurn);
    server.reset(newServer);
    myWidgetManager.setLimit(sf::IntRect(global::window.getSize().x / 2, 0, global::window.getSize().x / 2, global::window.getSize().y));
    actionType = new textWidgetClass("NONE");
    actionPlayer = new textWidgetClass("NONE");
    moveTotal = new textWidgetClass("0");
    moveNumber = new textWidgetClass("0");
    namePlayerPlay = new textWidgetClass("");
    namePlayerPlay->setSizeMessage(20);

    myWidgetManager.addToTmpList(new textWidgetClass("Type : "));
    myWidgetManager.addToTmpList(actionType);
    listForType = myWidgetManager.createList(HORIZONTAL, MIDDLE, 5);

    myWidgetManager.addToTmpList(new textWidgetClass("Joueur : "));
    myWidgetManager.addToTmpList(actionPlayer);
    listForPlayer = myWidgetManager.createList(HORIZONTAL, MIDDLE, 5);

    myWidgetManager.addToTmpList(new textWidgetClass("Action :"));
    myWidgetManager.addToTmpList(listForType);
    myWidgetManager.addToTmpList(listForPlayer);
    listForAction = myWidgetManager.createList(VERTICAL, MIDDLE, 8);

    myWidgetManager.addToTmpList(new textWidgetClass("Total : "));
    myWidgetManager.addToTmpList(moveTotal);
    listForMoveTotal = myWidgetManager.createList(HORIZONTAL, MIDDLE, 5);

    myWidgetManager.addToTmpList(new textWidgetClass("Pion : "));
    myWidgetManager.addToTmpList(moveNumber);
    listForMoveNumber = myWidgetManager.createList(HORIZONTAL, MIDDLE, 5);

    myWidgetManager.addToTmpList(new textWidgetClass("Déplacement :"));
    myWidgetManager.addToTmpList(listForMoveTotal);
    myWidgetManager.addToTmpList(listForMoveNumber);
    listForMove = myWidgetManager.createList(VERTICAL, MIDDLE, 8);

    myWidgetManager.addToTmpList(listForAction);
    myWidgetManager.addToTmpList(listForMove);
    myWidgetManager.setWidgetHere(myWidgetManager.createList(VERTICAL, MIDDLE, 125), MIDDLE_MIDDLE);

    myWidgetManager.setWidgetHere(namePlayerPlay, TOP_MIDDLE, 0, 5);
    myWidgetManager.setWidgetHere(new buttonWidgetClass("Abandon", std::bind(&serverClass::playerLeave, &*server)), BOTTOM_MIDDLE, 0, 5);
}

playStateClass::~playStateClass()
{

}

void playStateClass::update()
{
    typePlayer tmpPlayer;
    action tmpAction;
    int tmpNumber;

    sf::Event event;
    while(global::window.pollEvent(event))
    {
        if(event.type == sf::Event::Closed)
        {
            global::run = false;
        }
        else if(event.type == sf::Event::MouseButtonPressed)
        {
            if (event.mouseButton.button == sf::Mouse::Left)
            {
                int x = event.mouseButton.x;
                int y = event.mouseButton.y;
                if(x > server->getBordSize().x && x < global::window.getSize().x / 2 - server->getBordSize().x && y > server->getBordSize().y && y < global::window.getSize().y - server->getBordSize().y)
                {
                    x = (x - server->getBordSize().x) / server->getCaseSizeTray().x;
                    y = (y - server->getBordSize().y) / server->getCaseSizeTray().y;
                    server->update();
                    server->clickTo(x, y);
                }

                myWidgetManager.mouseClick(x, y);
            }
        }
        else if(event.type == sf::Event::MouseMoved)
        {
            myWidgetManager.mouseMove(event.mouseMove.x, event.mouseMove.y);
        }
        else if(event.type == sf::Event::KeyPressed)
        {
            if(event.key.code == sf::Keyboard::Escape)
            {
                global::gameStateStack.set(new mainMenuStateClass);
                return;
            }
            else if(event.key.code == sf::Keyboard::T)
            {
                server->startRecord();
            }
        }
        else if(event.type == sf::Event::KeyReleased)
        {
            if(event.key.code == sf::Keyboard::T)
            {
                server->stopRecord();
            }
        }
    }

    if(server->getGameReady() == false)
    {
        global::gameStateStack.set(new mainMenuStateClass);
        return;
    }

    myWidgetManager.update();
    server->update();
    tmpPlayer = server->getPlayerPlay();
    if(playerPlay != tmpPlayer)
    {
        playerPlay = tmpPlayer;
        printPlayer();
    }
    tmpAction = server->getCurrentAction();
    if(currentAction.action != tmpAction.action || currentAction.player != tmpAction.player)
    {
        if(currentAction.player != tmpAction.player)
        {
            if(global::soundType == ALL || global::soundType == END_TURN_ONLY)
            {
                if(tmpAction.player == playerPlay)
                {
                    soundForYourTurn.play();
                }
                else
                {
                    soundForEndTurn.play();
                }
            }
        }
        currentAction = tmpAction;
        printAction();
    }
    tmpNumber = server->getMoveForPlayer();
    if(tmpNumber != numberMoveTotal)
    {
        numberMoveTotal = tmpNumber;
        moveTotal->setMessage(intToStr(numberMoveTotal));
        myWidgetManager.widgetHasChanged();
    }
    tmpNumber = server->getMoveForNumber();
    if(tmpNumber != numberMoveNumber)
    {
        numberMoveNumber = tmpNumber;
        moveNumber->setMessage(intToStr(numberMoveNumber));
        myWidgetManager.widgetHasChanged();
    }
}

void playStateClass::draw()
{
    global::window.clear(sf::Color::White);
    server->draw();
    myWidgetManager.draw();
}

void playStateClass::printAction()
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

void playStateClass::printPlayer()
{
    std::string newName = "(vous jouez ";

    if(playerPlay == RED)
    {
        newName += "rouge";
    }
    else if(playerPlay == BLUE)
    {
        newName += "bleu";
    }
    else if(playerPlay == MAGENTA)
    {
        newName += "magenta";
    }
    else if(playerPlay == CYAN)
    {
        newName += "cyan";
    }

    newName += ")";

    namePlayerPlay->setMessage(newName);
    myWidgetManager.widgetHasChanged();
}

std::string playStateClass::intToStr(int thisInt)
{
    std::ostringstream oss;
    oss << thisInt;
    return oss.str();
}
