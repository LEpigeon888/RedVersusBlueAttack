#ifndef LEVEL_HPP
#define LEVEL_HPP

#include "structForGame.hpp"
#include "staticTray.hpp"

class levelClass
{
public:
    static bool loadLevel(std::string nameLevel, int& totalPlayer, int& totalMoveForPlayer, int& totalNumberForPlayer, int& totalMoveForNumberForPlayer, std::vector<sf::IntRect>& listOfRectPlace, staticTrayClass& staticTray);
    static void saveLevel(std::string nameLevel, int totalPlayer, int totalMoveForPlayer, int totalNumberForPlayer, int totalMoveForNumberForPlayer, const std::vector<sf::IntRect>& listOfRectPlace, const staticTrayClass& staticTray);
    static bool readFirstNumber(std::string& thisString, int& toThisInt);
    static bool readFirstNumber(std::string& thisString, float& toThisFloat);
private:
};

#endif
