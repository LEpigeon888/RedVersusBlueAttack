#include "widgetTextBox.hpp"

widgetTextBox::widgetTextBox(std::string baseMessage, std::string sizeMessageStr, typeMask newMask) :
    textWidgetClass(baseMessage + 'W')
{
    marginToText = sf::Vector2f(0, 0);
    messageToShow = baseMessage;
    maxChar = sizeMessageStr.size() - 1;
    focus = false;
    isReadOnly = false;
    slotIsSet = false;
    baseString = "";
    mask = newMask;
    setMessage(messageToShow);
    sizeMessage.setString(sizeMessageStr);
    sizeMessage.setFont(global::font);
    sizeMessage.setCharacterSize(global::sizeChar);
    adjustOrigin(sizeMessage);
    shape.setSize(sf::Vector2f(sizeMessage.getGlobalBounds().width + (marginToText.x * 2), sizeMessage.getGlobalBounds().height + (marginToText.y * 2)));
    shape.setOutlineColor(sf::Color::Black);
    shape.setOutlineThickness(2);
}

void widgetTextBox::draw()
{
    global::window.draw(shape);
    textWidgetClass::draw();
}

void widgetTextBox::update()
{
    if(focus == true && isReadOnly == false)
    {
        if(timer.getElapsedTime().asSeconds() > 0.5)
        {
            if(cursor.size() > 0)
            {
                cursor.clear();
            }
            else
            {
                cursor = '|';
            }
            timer.restart();
            textWidgetClass::setMessage(messageToShow + cursor);
        }
    }
}

void widgetTextBox::isFocused(bool focused, int x, int y)
{
    (void)x;
    (void)y;
    if(isReadOnly == false)
    {
        if(focused == true)
        {
            cursor = '|';
            textWidgetClass::setMessage(messageToShow + cursor);
            timer.restart();
            focus = true;
        }
        else
        {
            cursor.clear();
            textWidgetClass::setMessage(messageToShow + cursor);
            focus = false;
        }
    }

    if(focused == false && baseString != "" && messageToShow == "")
    {
        setMessage(baseString);
    }
}

void widgetTextBox::enteredText(char letter)
{
    if(isReadOnly == false)
    {
        if(letter > 31 && letter < 127 && letter != '|')
        {
            if(mask == INT && (letter < '0' || letter > '9'))
            {
                return;
            }
            if(messageToShow.size() < maxChar)
            {
                messageToShow += letter;
                textWidgetClass::setMessage(messageToShow + cursor);
            }
        }
        else if(letter == 8)
        {
            if(messageToShow.size() > 0)
            {
                messageToShow.erase(messageToShow.size() - 1, 1);
                textWidgetClass::setMessage(messageToShow + cursor);
            }
        }
        else if(letter == 13)
        {
            callSlot();
        }
    }
}

void widgetTextBox::callSlot()
{
    if(slotIsSet)
    {
        slot();
    }
}

sf::Vector2f widgetTextBox::getSize()
{
    return shape.getSize();
}

sf::FloatRect widgetTextBox::getBounds()
{
    return shape.getGlobalBounds();
}

std::string widgetTextBox::getMessage()
{
    return messageToShow;
}

void widgetTextBox::movePosition(int x, int y)
{
    textWidgetClass::movePosition(x, y);
    shape.move(x, y);
}

void widgetTextBox::setPosition(int x, int y)
{
    textWidgetClass::setPosition(x + marginToText.x, y + marginToText.y);
    shape.setPosition(x, y);
}

void widgetTextBox::setIsReadOnly(bool newReadOnly)
{
    isReadOnly = newReadOnly;
}

void widgetTextBox::setSlot(std::function<void(void)> newSlot)
{
    slot = newSlot;
    slotIsSet = true;
}

void widgetTextBox::setMarginToText(sf::Vector2f newMarginToText)
{
    marginToText = newMarginToText;
    shape.setSize(sf::Vector2f(sizeMessage.getGlobalBounds().width + (marginToText.x * 2), sizeMessage.getGlobalBounds().height + (marginToText.y * 2)));
}

void widgetTextBox::setMessage(std::string newMessage)
{
    textWidgetClass::setMessage(newMessage);
    messageToShow = newMessage;
}

void widgetTextBox::setBaseIfVoid(std::string newBase)
{
    baseString = newBase;
}

void widgetTextBox::setSizeMessage(int newSize)
{
    textWidgetClass::setSizeMessage(newSize);
    shape.setSize(sf::Vector2f(sizeMessage.getGlobalBounds().width + (marginToText.x * 2), sizeMessage.getGlobalBounds().height + (marginToText.y * 2)));
}

void widgetTextBox::setEdgeSize(int newEdgeSize)
{
    shape.setOutlineThickness(newEdgeSize);
}

void widgetTextBox::setEdgeColor(sf::Color newColor)
{
    shape.setOutlineColor(newColor);
}

void widgetTextBox::setFont(sf::Font newFont)
{
    textWidgetClass::setFont(newFont);
    shape.setSize(sf::Vector2f(sizeMessage.getGlobalBounds().width + (marginToText.x * 2), sizeMessage.getGlobalBounds().height + (marginToText.y * 2)));
}

void widgetTextBox::setPointerToText(std::string*& ptr)
{
    ptr = &messageToShow;
}
