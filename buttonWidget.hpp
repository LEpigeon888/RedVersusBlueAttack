#ifndef BUTTONWIDGET_HPP
#define BUTTONWIDGET_HPP

#include <functional>

#include "textWidget.hpp"

class buttonWidgetClass : public textWidgetClass
{
public:
    buttonWidgetClass(std::string newMessage, std::function<void(void)> newSlot, int newBoundsMargeY = 5);
    void isClicked(int x, int y);
    void isPointed(bool pointed, int x, int y);
    sf::Vector2f getSize();
    sf::FloatRect getBounds();
    void setPosition(int x, int y);
    void setBoundsMargeY(int newBoundsMargeY);
    void setColorMessage(sf::Color newColor);
    void setColorPointed(sf::Color newColorPointed);
private:
    std::function<void(void)> slot;
    sf::Color colorNotPointed;
    sf::Color colorPointed;
    bool widgetIsPointed;
    int boundsMargeY;
};

#endif
