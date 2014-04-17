#include "caseType.hpp"
#include "global.hpp"
#include <iostream>
caseTypeClass::caseTypeClass()
{
    isFirstTime = false;
    isSelected = false;
    spriteShape.setPosition(-1, -1);
    isPlain = false;
    timeToKill = false;
    isKilled = false;
}

caseTypeClass::caseTypeClass(typePlayer newPlayerOwner, bool newIsHead, int newNumber, sf::Vector2f newPosition, sf::Vector2f newCaseSizeTray, sf::Vector2f newBordSize, bool newIsSelected)
{
    isPlain = false;
    isFirstTime = true;
    timeToKill = false;
    isKilled = false;
    playerOwner = newPlayerOwner;
    isHead = newIsHead;
    number = newNumber;
    position = newPosition;
    caseSizeTray = newCaseSizeTray;
    bordSize = newBordSize;
    isSelected = newIsSelected;
    soundForPlace.reset(new sf::Sound);
    soundForPlace->setBuffer(global::soundManager->soundPlace);
    spriteShape.setPosition(-1, -1);
    spriteShape.setSize(sf::Vector2f(0, 0));
    spriteShape.setPosition(position.x * caseSizeTray.x + bordSize.x + (caseSizeTray.x / 2), position.y * caseSizeTray.y + bordSize.y + (caseSizeTray.y / 2));

    if(isHead == true)
    {
        spriteShape.setOutlineThickness(2);
        if(isSelected == true)
        {
            spriteShape.setOutlineColor(sf::Color::Yellow);
        }
        else
        {
            spriteShape.setOutlineColor(sf::Color::Green);
        }
    }
    else
    {
        spriteShape.setOutlineThickness(0);
    }

    if(playerOwner == RED)
    {
        spriteShape.setFillColor(sf::Color(255 - (75 * number), 0, 0));
    }
    else if(playerOwner == BLUE)
    {
        spriteShape.setFillColor(sf::Color(0, 0, 255 - (75 * number)));
    }
    else if(playerOwner == MAGENTA)
    {
        spriteShape.setFillColor(sf::Color(255 - (75 * number), 0, 255 - (75 * number)));
    }
    else if(playerOwner == CYAN)
    {
        spriteShape.setFillColor(sf::Color(0, 255 - (75 * number), 255 - (75 * number)));
    }
}

void caseTypeClass::update()
{
    if(isPlain == false)
    {
        spriteShape.move(-1, -1);
        spriteShape.setSize(sf::Vector2f(spriteShape.getSize().x + 2, spriteShape.getSize().y + 2));
        if(isHead == false && isSelected == false)
        {
            if(spriteShape.getSize().x > caseSizeTray.x)
            {
                spriteShape.setPosition(position.x * caseSizeTray.x + bordSize.x, position.y * caseSizeTray.y + bordSize.y);
                spriteShape.setSize(caseSizeTray);
                isPlain = true;
            }
        }
        else
        {
            if(spriteShape.getSize().x + 4 > caseSizeTray.x)
            {
                spriteShape.setPosition(position.x * caseSizeTray.x + bordSize.x + 2, position.y * caseSizeTray.y + bordSize.y + 2);
                spriteShape.setSize(sf::Vector2f(caseSizeTray.x - 4, caseSizeTray.y - 4));
                isPlain = true;
            }
        }
    }
    if(timeToKill == true && isPlain == true)
    {
        spriteShape.move(1, 1);
        spriteShape.setSize(sf::Vector2f(spriteShape.getSize().x - 2, spriteShape.getSize().y - 2));
        if(spriteShape.getSize().x <= 0)
        {
            timeToKill = false;
            isKilled = true;
        }
    }
    if(isFirstTime == true)
    {
        isFirstTime = false;
        if(global::soundType == ALL)
        {
            soundForPlace->play();
        }
    }
    else if(soundForPlace.get() != nullptr)
    {
        if(soundForPlace->getStatus() == sf::SoundSource::Status::Stopped)
        {
            soundForPlace.reset();
        }
    }
}

typePlayer caseTypeClass::getPlayer()
{
    return playerOwner;
}

int caseTypeClass::getNumber()
{
    return number;
}

bool caseTypeClass::getIsHead()
{
    return isHead;
}

bool caseTypeClass::getIsSelected()
{
    return isSelected;
}

sf::RectangleShape& caseTypeClass::sprite()
{
    return spriteShape;
}

void caseTypeClass::setIsHead(bool newIsHead)
{
    if(newIsHead != isHead)
    {
        isHead = newIsHead;
        if(isHead == false)
        {
            if(isSelected == false)
            {
                spriteShape.setOutlineThickness(0);
                if(isPlain == true)
                {
                    spriteShape.setSize(sf::Vector2f(spriteShape.getSize().x + 4, spriteShape.getSize().y + 4));
                    spriteShape.move(-2, -2);
                }
            }
        }
        else
        {
            if(isSelected == false)
            {
                spriteShape.setOutlineThickness(2);
                spriteShape.setOutlineColor(sf::Color::Green);
                spriteShape.setSize(sf::Vector2f(spriteShape.getSize().x - 4, spriteShape.getSize().y - 4));
                spriteShape.move(2, 2);
            }
        }
    }
}

void caseTypeClass::setIsSelected(bool newIsSelected)
{
    if(newIsSelected != isSelected)
    {
        isSelected = newIsSelected;
        if(isSelected == false)
        {
            if(isHead == false)
            {
                spriteShape.setOutlineThickness(0);
                if(isPlain == true)
                {
                    spriteShape.setSize(sf::Vector2f(spriteShape.getSize().x + 4, spriteShape.getSize().y + 4));
                    spriteShape.move(-2, -2);
                }
            }
            else
            {
                spriteShape.setOutlineColor(sf::Color::Green);
            }
        }
        else
        {
            if(isHead == false)
            {
                spriteShape.setOutlineThickness(2);
                spriteShape.setSize(sf::Vector2f(spriteShape.getSize().x - 4, spriteShape.getSize().y - 4));
                spriteShape.move(2, 2);
            }
            spriteShape.setOutlineColor(sf::Color::Yellow);
        }
    }
}

void caseTypeClass::kill()
{
    timeToKill = true;
}

bool caseTypeClass::getIsKilled()
{
    return isKilled;
}

bool caseTypeClass::getIsPlain()
{
    return isPlain;
}
