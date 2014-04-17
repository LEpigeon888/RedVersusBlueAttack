#ifndef STATICTRAY_HPP
#define STATICTRAY_HPP

#include "structForGame.hpp"

class staticTrayClass
{
public:
    staticTrayClass();
    void draw();
    void createLine();
    void updateWall();
    void addNewWall(sf::Vector2f firstPoint, sf::Vector2f secondPoint);
    sf::RectangleShape creatRectPlaceFor(typePlayer thisPlayer, sf::IntRect surfaceRect);
    sf::Vector2f sizeTray;
    sf::Vector2f bordSize;
    sf::Vector2f caseSizeTray;
    std::vector<wall> listOfWall;
    void setTakeHalfScreen(bool newVal);
private:
    std::deque<sf::RectangleShape> tabLine;
    bool takeHalfScreen;
};

#endif
