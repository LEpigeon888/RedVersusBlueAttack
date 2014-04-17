#include "widgetManager.hpp"

widgetManagerClass::widgetManagerClass()
{
    widgetHasFocus = nullptr;
}

void widgetManagerClass::update()
{
    for(widgetInfo& it : listOfWidget)
    {
        it.widget->update();
    }
}

void widgetManagerClass::draw()
{
    for(widgetInfo& it : listOfWidget)
    {
        it.widget->draw();
    }
}

void widgetManagerClass::mouseMove(int x, int y)
{
    for(widgetInfo& it : listOfWidget)
    {
        it.widget->isPointed(it.widget->getBounds().contains(x, y), x, y);
    }
}

void widgetManagerClass::mouseClick(int x, int y)
{
    if(widgetHasFocus != nullptr)
    {
        widgetHasFocus->isFocused(false, 0, 0);
        widgetHasFocus = nullptr;
    }
    for(widgetInfo& it : listOfWidget)
    {
        if(it.widget->getBounds().contains(x, y))
        {
            widgetHasFocus = it.widget.get();
            it.widget->isFocused(true, x, y);
            it.widget->isClicked(x, y);
            break;
        }
    }
}

void widgetManagerClass::textIsEntered(char letter)
{
    if(widgetHasFocus != nullptr)
    {
        widgetHasFocus->enteredText(letter);
    }
}

void widgetManagerClass::setLimit(sf::IntRect newLimits)
{
    limits = newLimits;
}

void widgetManagerClass::setWidgetHere(widgetClass* widget, typePosition positionToScreen, int marginX, int marginY, bool addToList)
{
    widgetInfo newWidget;

    switch(positionToScreen)
    {
        case LEFT_MIDDLE:
        {
            widget->setPosition(limits.left + marginX, limits.top + (limits.height - widget->getSize().y) / 2);
            break;
        }

        case MIDDLE_MIDDLE:
        {
            widget->setPosition(limits.left + (limits.width - widget->getSize().x) / 2, limits.top + (limits.height - widget->getSize().y) / 2);
            break;
        }

        case RIGHT_MIDDLE:
        {
            widget->setPosition(limits.left + limits.width - widget->getSize().x - marginX, limits.top + (limits.height - widget->getSize().y) / 2);
            break;
        }

        case TOP_MIDDLE:
        {
            widget->setPosition(limits.left + (limits.width - widget->getSize().x) / 2, limits.top + marginY);
            break;
        }

        case BOTTOM_MIDDLE:
        {
            widget->setPosition(limits.left + (limits.width - widget->getSize().x) / 2, limits.top + limits.height - widget->getSize().y - marginY);
            break;
        }

        case TOP_LEFT:
        {
            widget->setPosition(limits.left + marginX, limits.top + marginY);
            break;
        }

        case TOP_RIGHT:
        {
            widget->setPosition(limits.left + limits.width - widget->getSize().x - marginX, limits.top + marginY);
            break;
        }

        case BOTTOM_LEFT:
        {
            widget->setPosition(limits.left + marginX, limits.top + limits.height - widget->getSize().y - marginY);
            break;
        }

        case BOTTOM_RIGHT:
        {
            widget->setPosition(limits.left + limits.width - widget->getSize().x - marginX, limits.top + limits.height - widget->getSize().y - marginY);
            break;
        }

        default:
        {
            break;
        }
    }

    if(addToList == true)
    {
        newWidget.widget = std::unique_ptr<widgetClass>(widget);
        newWidget.positionToScreen = positionToScreen;
        newWidget.marginX = marginX;
        newWidget.marginY = marginY;
        listOfWidget.push_back(std::move(newWidget));
    }
}

void widgetManagerClass::addToTmpList(widgetClass* widget)
{
    tmpListOfWidget.push_back(std::unique_ptr<widgetClass>(widget));
}

widgetClass* widgetManagerClass::createList(direction theDirection, basicTypePosition positionOfWidget, int marginToWidget, int marginXWidget)
{
    widgetListClass* myList = new widgetListClass;

    for(std::unique_ptr<widgetClass>& widget : tmpListOfWidget)
    {
        myList->addWidgetForManage(widget.release());
    }
    tmpListOfWidget.clear();

    if(theDirection == VERTICAL)
    {
        myList->createVerticalList(positionOfWidget, marginToWidget, marginXWidget);
    }
    else
    {
        myList->createHorizontalList(positionOfWidget, marginToWidget);
    }

    return myList;
}

void widgetManagerClass::lastWidgetHasFocus()
{
    if(widgetHasFocus != nullptr)
    {
        widgetHasFocus->isFocused(false, 0, 0);
        widgetHasFocus = nullptr;
    }

    if(listOfWidget.size() > 0)
    {
        widgetHasFocus = listOfWidget.back().widget.get();
        widgetHasFocus->isFocused(true, 0, 0);
    }
}

void widgetManagerClass::lastTmpWidgetHasFocus()
{
    if(widgetHasFocus != nullptr)
    {
        widgetHasFocus->isFocused(false, 0, 0);
        widgetHasFocus = nullptr;
    }

    if(tmpListOfWidget.size() > 0)
    {
        widgetHasFocus = tmpListOfWidget.back().get();
        widgetHasFocus->isFocused(true, 0, 0);
    }
}

void widgetManagerClass::widgetHasChanged()
{
    for(widgetInfo& it : listOfWidget)
    {
        it.widget->changed();
        setWidgetHere(it.widget.get(), it.positionToScreen, it.marginX, it.marginY, false);
    }
}

void widgetManagerClass::clearAll()
{
    widgetHasFocus = nullptr;
    tmpListOfWidget.clear();
    listOfWidget.clear();
}
