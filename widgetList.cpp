#include "widgetList.hpp"

widgetListClass::widgetListClass()
{
    widgetHasFocus = nullptr;
}

void widgetListClass::addWidgetForManage(widgetClass* widget)
{
    listOfWidget.push_back(std::unique_ptr<widgetClass>(widget));
}

void widgetListClass::createVerticalList(basicTypePosition positionOfWidget, int marginToWidget, int marginXWidget)
{
    if(listOfWidget.size() != 0)
    {
        int currentPosY = 0;
        sizeWidget.y = (listOfWidget.size() - 1) * marginToWidget;

        for(std::unique_ptr<widgetClass>& ite : listOfWidget)
        {
            if(ite->getSize().x > sizeWidget.x)
            {
                sizeWidget.x = ite->getSize().x;
            }
            sizeWidget.y += ite->getSize().y;
        }

        for(std::unique_ptr<widgetClass>& ite : listOfWidget)
        {
            int relativePositionXWidget = 0;

            switch(positionOfWidget)
            {
                case LEFT:
                {
                    relativePositionXWidget = marginXWidget;
                    break;
                }

                case MIDDLE:
                {
                    relativePositionXWidget = (sizeWidget.x - ite->getSize().x) / 2;
                    break;
                }

                case RIGHT:
                {
                    relativePositionXWidget = sizeWidget.x - ite->getSize().x - marginXWidget;
                    break;
                }

                default:
                {
                    break;
                }
            }

            ite->setPosition(positionWidget.x + relativePositionXWidget, positionWidget.y + currentPosY);
            currentPosY += ite->getSize().y + marginToWidget;
        }

        typeOfList.directionOfList = VERTICAL;
        typeOfList.positionOfWidget = positionOfWidget;
        typeOfList.marginToWidget = marginToWidget;
        typeOfList.marginXWidget = marginXWidget;
    }
}

void widgetListClass::createHorizontalList(basicTypePosition positionOfWidget, int marginToWidget)
{
    if(listOfWidget.size() != 0)
    {
        int currentPosX = 0;
        sizeWidget.x = (listOfWidget.size() - 1) * marginToWidget;

        for(std::unique_ptr<widgetClass>& ite : listOfWidget)
        {
            if(ite->getSize().y > sizeWidget.y)
            {
                sizeWidget.y = ite->getSize().y;
            }
            sizeWidget.x += ite->getSize().x;
        }

        for(std::unique_ptr<widgetClass>& ite : listOfWidget)
        {
            int relativePositionYWidget = 0;

            switch(positionOfWidget)
            {
                case TOP:
                {
                    relativePositionYWidget = 0;
                    break;
                }

                case MIDDLE:
                {
                    relativePositionYWidget = (sizeWidget.y - ite->getSize().y) / 2;
                    break;
                }

                case BOTTOM:
                {
                    relativePositionYWidget = sizeWidget.y - ite->getSize().y;
                    break;
                }

                default:
                {
                    break;
                }
            }

            ite->setPosition(positionWidget.x + currentPosX, positionWidget.y + relativePositionYWidget);
            currentPosX += ite->getSize().x + marginToWidget;
        }

        typeOfList.directionOfList = HORIZONTAL;
        typeOfList.positionOfWidget = positionOfWidget;
        typeOfList.marginToWidget = marginToWidget;
    }
}

void widgetListClass::draw()
{
    for(std::unique_ptr<widgetClass>& it : listOfWidget)
    {
        it->draw();
    }
}

void widgetListClass::update()
{
    for(std::unique_ptr<widgetClass>& it : listOfWidget)
    {
        it->update();
    }
}

void widgetListClass::isClicked(int x, int y)
{
    for(std::unique_ptr<widgetClass>& it : listOfWidget)
    {
        if(it->getBounds().contains(x, y))
        {
            it->isClicked(x, y);
            break;
        }
    }
}

void widgetListClass::isPointed(bool pointed, int x, int y)
{
    for(std::unique_ptr<widgetClass>& it : listOfWidget)
    {
        it->isPointed(pointed == false ? false : it->getBounds().contains(x, y), x, y);
    }
}

void widgetListClass::enteredText(char letter)
{
    if(widgetHasFocus != nullptr)
    {
        widgetHasFocus->enteredText(letter);
    }
}

void widgetListClass::changed()
{
    for(std::unique_ptr<widgetClass>& it : listOfWidget)
    {
        it->changed();
    }

    if(typeOfList.directionOfList == HORIZONTAL)
    {
        createHorizontalList(typeOfList.positionOfWidget, typeOfList.marginToWidget);
    }
    else
    {
        createVerticalList(typeOfList.positionOfWidget, typeOfList.marginToWidget, typeOfList.marginXWidget);
    }
}

void widgetListClass::isFocused(bool focused, int x, int y)
{
    if(widgetHasFocus != nullptr)
    {
        widgetHasFocus->isFocused(false, x, y);
        widgetHasFocus = nullptr;
    }
    if(focused == true)
    {
        for(std::unique_ptr<widgetClass>& it : listOfWidget)
        {
            if(it->getBounds().contains(x, y))
            {
                widgetHasFocus = it.get();
                it->isFocused(true, x, y);
                break;
            }
        }
    }
}

sf::Vector2f widgetListClass::getSize()
{
    return sizeWidget;
}

sf::FloatRect widgetListClass::getBounds()
{
    return sf::FloatRect(positionWidget, sizeWidget);
}

void widgetListClass::movePosition(int x, int y)
{
    for(std::unique_ptr<widgetClass>& ite : listOfWidget)
    {
        ite->movePosition(x, y);
    }

    positionWidget.x += x;
    positionWidget.y += y;
}

void widgetListClass::setPosition(int x, int y)
{
    for(std::unique_ptr<widgetClass>& ite : listOfWidget)
    {
        ite->movePosition(-positionWidget.x, -positionWidget.y);
        ite->movePosition(x, y);
    }

    positionWidget.x = x;
    positionWidget.y = y;
}
