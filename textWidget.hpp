#ifndef TEXTWIDGET_HPP
#define TEXTWIDGET_HPP

#include "widget.hpp"

class textWidgetClass : public widgetClass
{
public:
    textWidgetClass(std::string newMessage);
    virtual void draw();
    virtual void isClicked(int x, int y) {(void)x; (void)y;}
    virtual void isPointed(bool pointed, int x, int y) {(void)pointed; (void)x; (void)y;}
    virtual void isFocused(bool focused, int x, int y) {(void)focused; (void)x; (void)y;}
    virtual void enteredText(char letter) {(void)letter;}
    virtual void changed() {}
    virtual sf::Vector2f getSize();
    virtual sf::FloatRect getBounds();
    virtual void movePosition(int x, int y);
    virtual void adjustOrigin(sf::Text thisMessage);
    virtual void setPosition(int x, int y);
    virtual void setMessage(std::string newMessage);
    virtual void setSizeMessage(int newSize);
    virtual void setColorMessage(sf::Color newColor);
    virtual void setFont(sf::Font newFont);
protected:
    sf::Text message;
};

#endif
