#include "textWidget.hpp"

textWidgetClass::textWidgetClass(std::string newMessage)
{
    message.setString(newMessage);
    message.setCharacterSize(global::sizeChar);
    message.setColor(sf::Color::Black);
    message.setFont(global::font);
    message.setOrigin(0, static_cast<int>(message.getLocalBounds().top));
}

void textWidgetClass::draw()
{
    global::window.draw(message);
}

sf::Vector2f textWidgetClass::getSize()
{
    return sf::Vector2f(getBounds().width, getBounds().height);
}

sf::FloatRect textWidgetClass::getBounds()
{
    return message.getGlobalBounds();
}

void textWidgetClass::movePosition(int x, int y)
{
    message.move(x, y);
}

void textWidgetClass::adjustOrigin(sf::Text thisMessage)
{
    message.setOrigin(0, static_cast<int>(thisMessage.getLocalBounds().top));
}

void textWidgetClass::setPosition(int x, int y)
{
    message.setPosition(x, y);
}

void textWidgetClass::setMessage(std::string newMessage)
{
    message.setString(newMessage);
}

void textWidgetClass::setSizeMessage(int newSize)
{
    message.setCharacterSize(newSize);
    message.setOrigin(0, static_cast<int>(message.getLocalBounds().top));
}

void textWidgetClass::setColorMessage(sf::Color newColor)
{
    message.setColor(newColor);
}

void textWidgetClass::setFont(sf::Font newFont)
{
    message.setFont(newFont);
    message.setOrigin(0, static_cast<int>(message.getLocalBounds().top));
}
