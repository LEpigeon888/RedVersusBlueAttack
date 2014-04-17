#include <fstream>
#include <cstdlib>
#include <deque>
#include <vector>
#include <sstream>
#include <SFML/Graphics.hpp>

#include "level.hpp"
#include <iostream>
bool levelClass::loadLevel(std::string nameLevel, int& totalPlayer, int& totalMoveForPlayer, int& totalNumberForPlayer, int& totalMoveForNumberForPlayer, std::vector<sf::IntRect>& listOfRectPlace, staticTrayClass& staticTray)
{
    std::ifstream file(nameLevel.c_str());
    staticTray.listOfWall.clear();
    listOfRectPlace.clear();

    if(file.is_open())
    {
        std::string line;
        std::string typeLine = "END";

        staticTray.sizeTray.x = 0;
        staticTray.sizeTray.y = 0;
        totalPlayer = 0;
        totalMoveForPlayer = 0;
        totalNumberForPlayer = 0;
        totalMoveForNumberForPlayer = 0;

        while(std::getline(file, line))
        {
            if(line == "END")
            {
                typeLine = "END";
            }

            if(typeLine == "SIZE_TRAY")
            {
                if(readFirstNumber(line, staticTray.sizeTray.x) == false)
                {
                    return false;
                }
                if(readFirstNumber(line, staticTray.sizeTray.y) == false)
                {
                    return false;
                }
            }
            else if(typeLine == "TOTAL_PLAYER")
            {
                if(readFirstNumber(line, totalPlayer) == false)
                {
                    return false;
                }
            }
            else if(typeLine == "TOTAL_MOVE_FOR_PLAYER")
            {
                if(readFirstNumber(line, totalMoveForPlayer) == false)
                {
                    return false;
                }
            }
            else if(typeLine == "TOTAL_NUMBER_FOR_PLAYER")
            {
                if(readFirstNumber(line, totalNumberForPlayer) == false)
                {
                    return false;
                }
            }
            else if(typeLine == "TOTAL_MOVE_FOR_NUMBER_FOR_PLAYER")
            {
                if(readFirstNumber(line, totalMoveForNumberForPlayer) == false)
                {
                    return false;
                }
            }
            else if(typeLine == "RECT_FOR_PLAYER_PLACE")
            {
                int poseX;
                int poseY;
                int sizeX;
                int sizeY;
                if(readFirstNumber(line, poseX) == false)
                {
                    return false;
                }
                if(readFirstNumber(line, poseY) == false)
                {
                    return false;
                }
                if(readFirstNumber(line, sizeX) == false)
                {
                    return false;
                }
                if(readFirstNumber(line, sizeY) == false)
                {
                    return false;
                }
                if(poseX < 0 || poseY < 0 || sizeX < 1 || sizeY < 1)
                {
                    return false;
                }
                listOfRectPlace.push_back(sf::IntRect(poseX, poseY, sizeX, sizeY));
            }
            else if(typeLine == "WALL")
            {
                int firstPointX;
                int firstPointY;
                int secondPointX;
                int secondPointY;
                if(readFirstNumber(line, firstPointX) == false)
                {
                    return false;
                }
                if(readFirstNumber(line, firstPointY) == false)
                {
                    return false;
                }
                if(readFirstNumber(line, secondPointX) == false)
                {
                    return false;
                }
                if(readFirstNumber(line, secondPointY) == false)
                {
                    return false;
                }
                if(firstPointX < 0 || firstPointY < 0 || secondPointX < 0 || secondPointY < 0 || (firstPointX != secondPointX && firstPointY != secondPointY))
                {
                    return false;
                }
                staticTray.addNewWall(sf::Vector2f(firstPointX, firstPointY), sf::Vector2f(secondPointX, secondPointY));
            }
            else if(typeLine != "END")
            {
                return false;
            }

            if(typeLine == "END")
            {
                typeLine = line;
            }
        }

        if(staticTray.sizeTray.x < 1 || staticTray.sizeTray.y < 1 || totalPlayer < 1 || totalMoveForPlayer < 1 || totalNumberForPlayer < 1 || totalMoveForNumberForPlayer < 1)
        {
            return false;
        }

        if(file.bad() == true || (file.eof() == false && file.fail() == true))
        {
            return false;
        }
        else if(listOfRectPlace.size() != static_cast<unsigned int>(totalPlayer))
        {
            return false;
        }

        file.close();
    }
    else
    {
        return false;
    }

    return true;
}

void levelClass::saveLevel(std::string nameLevel, int totalPlayer, int totalMoveForPlayer, int totalNumberForPlayer, int totalMoveForNumberForPlayer, const std::vector<sf::IntRect>& listOfRectPlace, const staticTrayClass& staticTray)
{
    std::ofstream file(nameLevel.c_str());

    if(file.is_open())
    {
        file << "SIZE_TRAY" << std::endl;
        file << staticTray.sizeTray.x << " " << staticTray.sizeTray.y << std::endl;
        file << "END" << std::endl;
        file << "TOTAL_PLAYER" << std::endl;
        file << totalPlayer << std::endl;
        file << "END" << std::endl;
        file << "TOTAL_MOVE_FOR_PLAYER" << std::endl;
        file << totalMoveForPlayer << std::endl;
        file << "END" << std::endl;
        file << "TOTAL_NUMBER_FOR_PLAYER" << std::endl;
        file << totalNumberForPlayer << std::endl;
        file << "END" << std::endl;
        file << "TOTAL_MOVE_FOR_NUMBER_FOR_PLAYER" << std::endl;
        file << totalMoveForNumberForPlayer << std::endl;
        file << "END" << std::endl;
        file << "RECT_FOR_PLAYER_PLACE" << std::endl;
        for(const sf::IntRect& rect : listOfRectPlace)
        {
            file << rect.left << " " << rect.top << " " << rect.width << " " << rect.height << std::endl;
        }
        file << "END" << std::endl;
        file << "WALL" << std::endl;
        for(const wall& thisWall : staticTray.listOfWall)
        {
            file << thisWall.firstPoint.x << " " << thisWall.firstPoint.y << " " << thisWall.secondPoint.x << " " << thisWall.secondPoint.y << std::endl;
        }
        file << "END" << std::endl;
        file.close();
    }
}

bool levelClass::readFirstNumber(std::string& thisString, float& toThisFloat)
{
    int tmpInt;
    if(readFirstNumber(thisString, tmpInt) == false)
    {
        return false;
    }
    else
    {
        toThisFloat = tmpInt;
        return true;
    }
}

bool levelClass::readFirstNumber(std::string& thisString, int& toThisInt)
{
    size_t spacePos = thisString.find(' ');
    std::string tmpStrInt = thisString.substr(0, spacePos);
    std::istringstream iss(tmpStrInt);

    if(spacePos == std::string::npos)
    {
        thisString.erase(0);
    }
    else
    {
        thisString.erase(0, spacePos + 1);
    }

    if(iss >> toThisInt)
    {
        std::ostringstream oss;
        if(oss << toThisInt)
        {
            if(oss.str() != tmpStrInt)
            {
                return false;
            }
            else
            {
                return true;
            }
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}
