#ifndef WIDGET_HPP
#define WIDGET_HPP

#include <SFML/Graphics.hpp>

#include "global.hpp"

class widgetClass
{
public:
    virtual ~widgetClass() {}
    virtual void draw() = 0;
    virtual void update() {}
    virtual void isClicked(int x, int y) = 0;
    virtual void isPointed(bool pointed, int x, int y) = 0;
    virtual void isFocused(bool focused, int x, int y) = 0;
    virtual void enteredText(char letter) = 0;
    virtual void changed() = 0;
    virtual sf::Vector2f getSize() = 0;
    virtual sf::FloatRect getBounds() = 0;
    virtual void movePosition(int x, int y) = 0;
    virtual void setPosition(int x, int y) = 0;
};

#endif
