#include "buttonWidget.hpp"

buttonWidgetClass::buttonWidgetClass(std::string newMessage, std::function<void(void)> newSlot, int newBoundsMargeY) :
    textWidgetClass(newMessage)
{
    slot = newSlot;
    boundsMargeY = newBoundsMargeY;
    colorNotPointed = sf::Color::Black;
    colorPointed = global::grey;
    widgetIsPointed = false;
}

void buttonWidgetClass::isClicked(int x, int y)
{
    (void)x;
    (void)y;
    slot();
}

void buttonWidgetClass::isPointed(bool pointed, int x, int y)
{
    (void)x;
    (void)y;
    if(pointed != widgetIsPointed)
    {
        if(pointed == true)
        {
            message.setColor(colorPointed);
        }
        else
        {
            message.setColor(colorNotPointed);
        }

        widgetIsPointed = pointed;
    }
}

sf::Vector2f buttonWidgetClass::getSize()
{
    return sf::Vector2f(getBounds().width, getBounds().height);
}

sf::FloatRect buttonWidgetClass::getBounds()
{
    sf::FloatRect bounds = message.getGlobalBounds();
    bounds.height += boundsMargeY * 2;
    bounds.top -= boundsMargeY;
    return bounds;
}

void buttonWidgetClass::setPosition(int x, int y)
{
    message.setPosition(x, y + boundsMargeY);
}

void buttonWidgetClass::setBoundsMargeY(int newBoundsMargeY)
{
    boundsMargeY = newBoundsMargeY;
}

void buttonWidgetClass::setColorMessage(sf::Color newColor)
{
    textWidgetClass::setColorMessage(newColor);
    colorNotPointed = newColor;
    widgetIsPointed = !widgetIsPointed;
    isPointed(!widgetIsPointed, 0, 0);
}

void buttonWidgetClass::setColorPointed(sf::Color newColorPointed)
{
    colorPointed = newColorPointed;
    widgetIsPointed = !widgetIsPointed;
    isPointed(!widgetIsPointed, 0, 0);
}
