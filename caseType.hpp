#ifndef CASETYPE_HPP
#define CASETYPE_HPP

#include <memory>
#include <SFML/Graphics.hpp>

#include "soundManager.hpp"
#include "typeForGame.hpp"

class caseTypeClass
{
public:
    caseTypeClass();
    caseTypeClass(typePlayer newPlayerOwner, bool newIsHead, int newNumber, sf::Vector2f position, sf::Vector2f newCaseSizeTray, sf::Vector2f bordSize, bool newIsSelected = false);
    void update();
    typePlayer getPlayer();
    int getNumber();
    bool getIsHead();
    bool getIsSelected();
    sf::RectangleShape& sprite();
    void setIsHead(bool newIsHead);
    void setIsSelected(bool newIsSelected);
    void kill();
    bool getIsKilled();
    bool getIsPlain();
private:
    std::unique_ptr<sf::Sound> soundForPlace;
    typePlayer playerOwner;
    sf::RectangleShape spriteShape;
    sf::Vector2f caseSizeTray;
    sf::Vector2f position;
    sf::Vector2f bordSize;
    int number;
    bool isHead;
    bool isSelected;
    bool isPlain;
    bool isFirstTime;
    bool timeToKill;
    bool isKilled;
};

#endif
