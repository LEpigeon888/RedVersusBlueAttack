#ifndef WIDGETTEXTBOX_HPP
#define WIDGETTEXTBOX_HPP

#include "textWidget.hpp"

enum typeMask {INT, STRING};

class widgetTextBox : public textWidgetClass
{
public:
    widgetTextBox(std::string baseMessage, std::string sizeMessageStr, typeMask newMask);
    void draw();
    void update();
    void isFocused(bool focused, int x, int y);
    void enteredText(char letter);
    void callSlot();
    sf::Vector2f getSize();
    sf::FloatRect getBounds();
    std::string getMessage();
    void movePosition(int x, int y);
    void setPosition(int x, int y);
    void setIsReadOnly(bool newReadOnly);
    void setSlot(std::function<void(void)> newSlot);
    void setMarginToText(sf::Vector2f newMarginToText);
    void setMessage(std::string newMessage);
    void setBaseIfVoid(std::string newBase);
    void setSizeMessage(int newSize);
    void setEdgeSize(int newEdgeSize);
    void setEdgeColor(sf::Color newColor);
    void setFont(sf::Font newFont);
    void setPointerToText(std::string*& ptr);
private:
    sf::RectangleShape shape;
    sf::Vector2f marginToText;
    std::string messageToShow;
    std::string cursor;
    std::string baseString;
    sf::Text sizeMessage;
    unsigned int maxChar;
    bool focus;
    bool slotIsSet;
    typeMask mask;
    sf::Clock timer;
    std::function<void(void)> slot;
    bool isReadOnly;
};

#endif

