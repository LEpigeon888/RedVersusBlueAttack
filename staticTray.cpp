#include "staticTray.hpp"
#include "global.hpp"

staticTrayClass::staticTrayClass()
{
    takeHalfScreen = true;
}

void staticTrayClass::draw()
{
    for(sf::RectangleShape& it : tabLine)
    {
        global::window.draw(it);
    }
    for(wall& it : listOfWall)
    {
        global::window.draw(it.sprite);
    }
}

void staticTrayClass::createLine()
{
    tabLine.clear();
    tabLine.resize(sizeTray.x + sizeTray.y + 2);

    for(int i = 0; i < sizeTray.x + 1; ++i)
    {
        sf::RectangleShape tmpRect;
        tmpRect.setFillColor(global::grey);
        tmpRect.setSize(sf::Vector2f(2, global::window.getSize().y - bordSize.y * 2));
        tmpRect.setPosition(i * caseSizeTray.x - 1 + bordSize.x, bordSize.y);
        tabLine.push_back(tmpRect);
    }

    for(int i = 0; i < sizeTray.y + 1; ++i)
    {
        sf::RectangleShape tmpRect;
        tmpRect.setFillColor(global::grey);
        tmpRect.setSize(sf::Vector2f(global::window.getSize().x / (takeHalfScreen == true ? 2 : 1) - bordSize.x * 2, 2));
        tmpRect.setPosition(bordSize.x, i * caseSizeTray.y - 1 + bordSize.y);
        tabLine.push_back(tmpRect);
    }
}

void staticTrayClass::updateWall()
{
    for(wall& it : listOfWall)
    {
        it.sprite.setFillColor(sf::Color::Black);
        it.sprite.setSize(sf::Vector2f((it.secondPoint.x - it.firstPoint.x) * caseSizeTray.x + 2, (it.secondPoint.y - it.firstPoint.y) * caseSizeTray.y + 2));
        it.sprite.setPosition(it.firstPoint.x * caseSizeTray.x + bordSize.x - 1, it.firstPoint.y * caseSizeTray.y + bordSize.y - 1);
    }
}
void staticTrayClass::addNewWall(sf::Vector2f firstPoint, sf::Vector2f secondPoint)
{
    wall newWall;

    if(firstPoint.y > secondPoint.y || (firstPoint.y == secondPoint.y && firstPoint.x > secondPoint.x))
    {
        sf::Vector2f tmpPoint;
        tmpPoint = firstPoint;
        firstPoint = secondPoint;
        secondPoint = tmpPoint;
    }

    newWall.firstPoint = firstPoint;
    newWall.secondPoint = secondPoint;
    newWall.sprite.setFillColor(sf::Color::Black);
    newWall.sprite.setSize(sf::Vector2f((newWall.secondPoint.x - newWall.firstPoint.x) * caseSizeTray.x + 2, (newWall.secondPoint.y - newWall.firstPoint.y) * caseSizeTray.y + 2));
    newWall.sprite.setPosition(newWall.firstPoint.x * caseSizeTray.x + bordSize.x - 1, newWall.firstPoint.y * caseSizeTray.y + bordSize.y - 1);
    listOfWall.push_back(std::move(newWall));
}

sf::RectangleShape staticTrayClass::creatRectPlaceFor(typePlayer thisPlayer, sf::IntRect surfaceRect)
{
    sf::RectangleShape rectangle;

    if(thisPlayer == RED)
    {
        rectangle.setFillColor(sf::Color(sf::Color::Red.r, sf::Color::Red.g, sf::Color::Red.b, 128));
    }
    else if(thisPlayer == BLUE)
    {
        rectangle.setFillColor(sf::Color(sf::Color::Blue.r, sf::Color::Blue.g, sf::Color::Blue.b, 128));
    }
    else if(thisPlayer == MAGENTA)
    {
        rectangle.setFillColor(sf::Color(sf::Color::Magenta.r, sf::Color::Magenta.g, sf::Color::Magenta.b, 128));
    }
    else if(thisPlayer == CYAN)
    {
        rectangle.setFillColor(sf::Color(sf::Color::Cyan.r, sf::Color::Cyan.g, sf::Color::Cyan.b, 128));
    }

    rectangle.setSize(sf::Vector2f(surfaceRect.width * caseSizeTray.x, surfaceRect.height * caseSizeTray.y));
    rectangle.setPosition(surfaceRect.left * caseSizeTray.x + bordSize.x, surfaceRect.top * caseSizeTray.y + bordSize.y);

    return rectangle;
}

void staticTrayClass::setTakeHalfScreen(bool newVal)
{
    takeHalfScreen = newVal;
}
