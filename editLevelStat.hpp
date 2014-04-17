#ifndef EDITLEVELSTAT_HPP
#define EDITLEVELSTAT_HPP

#include "gameState.hpp"
#include "staticTray.hpp"
#include "widgetManager.hpp"

class widgetTextBox;

class editLevelClass : public gameStateClass
{
public:
    editLevelClass();
    void update();
    void draw();
    void updateTray();
    void setNewTray();
    void setSpriteForTmpWall();
    void loadLevel();
    void saveLevel();
    std::string intToStr(int thisInt);
private:
    staticTrayClass staticTray;
    std::deque<sf::RectangleShape> listOfRect;
    std::deque<sf::IntRect> rectForPlayerPlace;
    wall tmpWall;
    bool widgetManagerForTextIsActive;
    bool drawRect;
    int totPlayer;
    typePlayer playerForRect;
    widgetManagerClass widgetManagerForText;
    widgetTextBox* textBoxWidgetForText;
    widgetManagerClass myWidgetManager;
    widgetTextBox* textBoxWidth;
    widgetTextBox* textBoxHeight;
    widgetTextBox* textBoxNbPlayer;
    widgetTextBox* textBoxTotNb;
    widgetTextBox* textBoxMoveTot;
    widgetTextBox* textBoxMoveNb;
};

#endif

