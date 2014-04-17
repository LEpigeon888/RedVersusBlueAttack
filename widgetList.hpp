#ifndef WIDGETLIST_HPP
#define WIDGETLIST_HPP

#include "widget.hpp"

enum basicTypePosition {LEFT, MIDDLE, RIGHT, TOP, BOTTOM};
enum direction {HORIZONTAL, VERTICAL};

struct typeList
{
    direction directionOfList;
    basicTypePosition positionOfWidget;
    int marginToWidget;
    int marginXWidget;
};

class widgetListClass : public widgetClass
{
public:
    widgetListClass();
    void addWidgetForManage(widgetClass* widget);
    void createVerticalList(basicTypePosition positionOfWidget, int marginToWidget = 0, int marginXWidget = 0);
    void createHorizontalList(basicTypePosition positionOfWidget, int marginToWidget = 0);
    void draw();
    void update();
    void isClicked(int x, int y);
    void isPointed(bool pointed, int x, int y);
    void isFocused(bool focused, int x, int y);
    void enteredText(char letter);
    void changed();
    sf::Vector2f getSize();
    sf::FloatRect getBounds();
    void movePosition(int x, int y);
    void setPosition(int x, int y);
private:
    std::vector<std::unique_ptr<widgetClass>> listOfWidget;
    typeList typeOfList;
    widgetClass* widgetHasFocus;
    sf::Vector2f sizeWidget;
    sf::Vector2f positionWidget;
};

#endif


