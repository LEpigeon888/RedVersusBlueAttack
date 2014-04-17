#ifndef STRUCTFORGAME_HPP
#define STRUCTFORGAME_HPP

#include <SFML/Graphics.hpp>
#include <deque>
#include <map>

#include "caseType.hpp"
#include "typeForGame.hpp"

struct wall
{
    sf::Vector2f firstPoint;
    sf::Vector2f secondPoint;
    sf::RectangleShape sprite;
};

struct action
{
    typeAction action;
    typePlayer player;
};

typedef std::pair<int, int> point;

struct aPlayer
{
    int restMove;
    std::deque<int> restMoveForNumber;
    point selectedCase;
    int restNumber;
    sf::IntRect rectForPlace;
};

struct theGame
{
    action currentAction;
    std::map<point, caseTypeClass> tray;
    int totalPlayer;
    int totalMoveForPlayer;
    int totalNumberForPlayer;
    int totalMoveForNumberForPlayer;
    std::deque<aPlayer> themPlayer;
};

#endif
