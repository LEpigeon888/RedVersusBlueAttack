#ifndef WIDGETMANAGER_HPP
#define WIDGETMANAGER_HPP

#include "widget.hpp"
#include "widgetList.hpp"

enum typePosition {LEFT_MIDDLE, MIDDLE_MIDDLE, RIGHT_MIDDLE, TOP_MIDDLE, BOTTOM_MIDDLE, TOP_LEFT, TOP_RIGHT, BOTTOM_LEFT, BOTTOM_RIGHT};

struct widgetInfo
{
    std::unique_ptr<widgetClass> widget;
    typePosition positionToScreen;
    int marginX;
    int marginY;
};

class widgetManagerClass
{
public:
    widgetManagerClass();
    void update();
    void draw();
    void mouseMove(int x, int y);
    void mouseClick(int x, int y);
    void textIsEntered(char letter);
    void setLimit(sf::IntRect newLimits);
    void setWidgetHere(widgetClass* widget, typePosition positionToScreen, int marginX = 0, int marginY = 0, bool addToList = true);
    void addToTmpList(widgetClass* widget);
    widgetClass* createList(direction theDirection, basicTypePosition positionOfWidget, int marginToWidget = 0, int marginXWidget = 0);
    void lastWidgetHasFocus();
    void lastTmpWidgetHasFocus();
    void widgetHasChanged();
    void clearAll();
private:
    std::vector<widgetInfo> listOfWidget;
    std::vector<std::unique_ptr<widgetClass>> tmpListOfWidget;
    widgetClass* widgetHasFocus;
    sf::IntRect limits;
};

#endif
