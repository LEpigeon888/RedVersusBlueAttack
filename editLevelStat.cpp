#include <sstream>

#include "editLevelStat.hpp"
#include "mainMenuState.hpp"
#include "widgetTextBox.hpp"
#include "widgetList.hpp"
#include "buttonWidget.hpp"
#include "level.hpp"
#include "global.hpp"

editLevelClass::editLevelClass()
{
    widgetClass* myListOfTextBox;

    staticTray.sizeTray.x = 20;
    staticTray.sizeTray.y = 30;
    tmpWall.firstPoint.x = -1;
    totPlayer = 2;
    widgetManagerForTextIsActive = false;
    drawRect = true;
    playerForRect = NO_PLAYER;
    textBoxWidgetForText = new widgetTextBox("", "WWWWWWWWWWWWWWgWWWWWWWWWWWWWW", STRING);
    textBoxWidth = new widgetTextBox("20", "lWWW", INT);
    textBoxHeight = new widgetTextBox("30", "lWWW", INT);
    textBoxNbPlayer = new widgetTextBox("2", "lW", INT);
    textBoxTotNb = new widgetTextBox("2", "lW", INT);
    textBoxMoveTot = new widgetTextBox("2", "lWW", INT);
    textBoxMoveNb = new widgetTextBox("2", "lWW", INT);
    textBoxWidth->setBaseIfVoid("0");
    textBoxHeight->setBaseIfVoid("0");
    textBoxNbPlayer->setBaseIfVoid("0");
    textBoxTotNb->setBaseIfVoid("0");
    textBoxMoveTot->setBaseIfVoid("0");
    textBoxMoveNb->setBaseIfVoid("0");
    myWidgetManager.setLimit(sf::IntRect(global::window.getSize().x / 2, 0, global::window.getSize().x / 2, global::window.getSize().y));
    widgetManagerForText.setLimit(sf::IntRect(0, 0, global::window.getSize().x, global::window.getSize().y));

    myWidgetManager.addToTmpList(textBoxWidth);
    myWidgetManager.addToTmpList(new textWidgetClass("x"));
    myWidgetManager.addToTmpList(textBoxHeight);
    myListOfTextBox = myWidgetManager.createList(HORIZONTAL, MIDDLE, 5);

    myWidgetManager.addToTmpList(new textWidgetClass("Taille :"));
    myWidgetManager.addToTmpList(myListOfTextBox);
    myWidgetManager.addToTmpList(new textWidgetClass("Nombre de joueur :"));
    myWidgetManager.addToTmpList(textBoxNbPlayer);
    myWidgetManager.addToTmpList(new textWidgetClass("Nombre de pion :"));
    myWidgetManager.addToTmpList(textBoxTotNb);
    myWidgetManager.addToTmpList(new textWidgetClass("Pts de mvmnt total :"));
    myWidgetManager.addToTmpList(textBoxMoveTot);
    myWidgetManager.addToTmpList(new textWidgetClass("Pts de mvmnt par pion :"));
    myWidgetManager.addToTmpList(textBoxMoveNb);
    myWidgetManager.setWidgetHere(myWidgetManager.createList(VERTICAL, MIDDLE, 20), MIDDLE_MIDDLE);

    myWidgetManager.setWidgetHere(new buttonWidgetClass("appliquer", std::bind(&editLevelClass::setNewTray, this)), BOTTOM_MIDDLE, 0, 5);

    widgetManagerForText.setWidgetHere(textBoxWidgetForText, MIDDLE_MIDDLE);
    widgetManagerForText.lastWidgetHasFocus();

    setNewTray();
}

void editLevelClass::update()
{
    sf::Event event;
    while(global::window.pollEvent(event))
    {
        if(event.type == sf::Event::Closed)
        {
            global::run = false;
        }
        else if(event.type == sf::Event::MouseButtonPressed)
        {
            if(event.mouseButton.button == sf::Mouse::Left)
            {
                if(widgetManagerForTextIsActive == false)
                {
                    if(playerForRect == NO_PLAYER)
                    {
                        if(tmpWall.firstPoint.x == -1)
                        {
                            int x = event.mouseButton.x;
                            int y = event.mouseButton.y;
                            if(x > staticTray.bordSize.x && x < global::window.getSize().x / 2 - staticTray.bordSize.x && y > staticTray.bordSize.y && y < global::window.getSize().y - staticTray.bordSize.y)
                            {
                                tmpWall.firstPoint.x = static_cast<int>((x - staticTray.bordSize.x + (staticTray.caseSizeTray.x / 2)) / staticTray.caseSizeTray.x);
                                tmpWall.firstPoint.y = static_cast<int>((y - staticTray.bordSize.y + (staticTray.caseSizeTray.y / 2)) / staticTray.caseSizeTray.y);
                                tmpWall.secondPoint = tmpWall.firstPoint;
                            }
                        }
                        else
                        {
                            if(tmpWall.firstPoint != tmpWall.secondPoint)
                            {
                                staticTray.addNewWall(tmpWall.firstPoint, tmpWall.secondPoint);
                            }
                            tmpWall.firstPoint.x = -1;
                        }
                    }
                    else
                    {
                        if(rectForPlayerPlace[playerForRect].left == -1)
                        {
                            int x = event.mouseButton.x;
                            int y = event.mouseButton.y;
                            if(x > staticTray.bordSize.x && x < global::window.getSize().x / 2 - staticTray.bordSize.x && y > staticTray.bordSize.y && y < global::window.getSize().y - staticTray.bordSize.y)
                            {
                                rectForPlayerPlace[playerForRect].left = (x - staticTray.bordSize.x) / staticTray.caseSizeTray.x;
                                rectForPlayerPlace[playerForRect].top = (y - staticTray.bordSize.y) / staticTray.caseSizeTray.y;
                                rectForPlayerPlace[playerForRect].width = 1;
                                rectForPlayerPlace[playerForRect].height = 1;
                            }
                        }
                        else
                        {
                            playerForRect = NO_PLAYER;
                        }
                    }
                }
            }
            else if(event.mouseButton.button == sf::Mouse::Right)
            {
                if(widgetManagerForTextIsActive == false)
                {
                    for(std::vector<wall>::iterator it = staticTray.listOfWall.begin(); it != staticTray.listOfWall.end(); ++it)
                    {
                        if(it->sprite.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
                        {
                            staticTray.listOfWall.erase(it);
                            break;
                        }
                    }
                }
            }
            if(widgetManagerForTextIsActive == true)
            {
                widgetManagerForText.mouseClick(event.mouseButton.x, event.mouseButton.y);
            }
            else
            {
                myWidgetManager.mouseClick(event.mouseButton.x, event.mouseButton.y);
            }
        }
        else if(event.type == sf::Event::MouseMoved)
        {
            if(widgetManagerForTextIsActive == false)
            {
                if(playerForRect == NO_PLAYER)
                {
                    if(tmpWall.firstPoint.x != -1)
                    {
                        int x = event.mouseMove.x;
                        int y = event.mouseMove.y;
                        if(x > staticTray.bordSize.x && x < global::window.getSize().x / 2 - staticTray.bordSize.x && y > staticTray.bordSize.y && y < global::window.getSize().y - staticTray.bordSize.y)
                        {
                            tmpWall.secondPoint.x = static_cast<int>((x - staticTray.bordSize.x + (staticTray.caseSizeTray.x / 2)) / staticTray.caseSizeTray.x);
                            tmpWall.secondPoint.y = static_cast<int>((y - staticTray.bordSize.y + (staticTray.caseSizeTray.y / 2)) / staticTray.caseSizeTray.y);
                            if(tmpWall.firstPoint.x > tmpWall.secondPoint.x && tmpWall.firstPoint.y > tmpWall.secondPoint.y)
                            {
                                tmpWall.secondPoint = tmpWall.firstPoint;
                            }
                            else
                            {
                                if(tmpWall.secondPoint.x - tmpWall.firstPoint.x < tmpWall.secondPoint.y - tmpWall.firstPoint.y)
                                {
                                    tmpWall.secondPoint.x = tmpWall.firstPoint.x;
                                }
                                else
                                {
                                    tmpWall.secondPoint.y = tmpWall.firstPoint.y;
                                }
                            }
                        }
                    }
                }
                else
                {
                    if(rectForPlayerPlace[playerForRect].left != -1)
                    {
                        int x = event.mouseMove.x;
                        int y = event.mouseMove.y;
                        if(x > staticTray.bordSize.x && x < global::window.getSize().x / 2 - staticTray.bordSize.x && y > staticTray.bordSize.y && y < global::window.getSize().y - staticTray.bordSize.y)
                        {
                            x = (x - staticTray.bordSize.x) / staticTray.caseSizeTray.x;
                            y = (y - staticTray.bordSize.y) / staticTray.caseSizeTray.y;
                            if(x < rectForPlayerPlace[playerForRect].left)
                            {
                                rectForPlayerPlace[playerForRect].width = 1;
                            }
                            else
                            {
                                rectForPlayerPlace[playerForRect].width = x - rectForPlayerPlace[playerForRect].left + 1;
                            }
                            if(y < rectForPlayerPlace[playerForRect].top)
                            {
                                rectForPlayerPlace[playerForRect].height = 1;
                            }
                            else
                            {
                                rectForPlayerPlace[playerForRect].height = y - rectForPlayerPlace[playerForRect].top + 1;
                            }
                        }
                    }
                }

                if(sf::Mouse::isButtonPressed(sf::Mouse::Right))
                {
                    for(std::vector<wall>::iterator it = staticTray.listOfWall.begin(); it != staticTray.listOfWall.end(); ++it)
                    {
                        if(it->sprite.getGlobalBounds().contains(event.mouseMove.x, event.mouseMove.y))
                        {
                            staticTray.listOfWall.erase(it);
                            break;
                        }
                    }
                }
            }

            if(widgetManagerForTextIsActive == true)
            {
                widgetManagerForText.mouseMove(event.mouseMove.x, event.mouseMove.y);
            }
            else
            {
                myWidgetManager.mouseMove(event.mouseMove.x, event.mouseMove.y);
            }
        }
        else if(event.type == sf::Event::TextEntered)
        {
            if(event.text.unicode < 128)
            {
                if(widgetManagerForTextIsActive == true)
                {
                    widgetManagerForText.textIsEntered(static_cast<char>(event.text.unicode));
                }
                else
                {
                    myWidgetManager.textIsEntered(static_cast<char>(event.text.unicode));
                }
            }
        }
        else if(event.type == sf::Event::KeyPressed)
        {
            if(event.key.code == sf::Keyboard::Escape)
            {
                global::gameStateStack.set(new mainMenuStateClass);
                return;
            }
            else if(event.key.code == sf::Keyboard::L)
            {
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
                {
                    widgetManagerForTextIsActive = !widgetManagerForTextIsActive;
                    textBoxWidgetForText->setSlot(std::bind(&editLevelClass::loadLevel, this));
                }
            }
            else if(event.key.code == sf::Keyboard::S)
            {
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
                {
                    widgetManagerForTextIsActive = !widgetManagerForTextIsActive;
                    textBoxWidgetForText->setSlot(std::bind(&editLevelClass::saveLevel, this));
                }
            }
            else if(event.key.code == sf::Keyboard::D)
            {
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
                {
                    drawRect = !drawRect;
                }
            }
            else if(event.key.code == sf::Keyboard::R)
            {
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && totPlayer > 0)
                {
                    playerForRect = RED;
                    rectForPlayerPlace[0] = sf::IntRect(-1, -1, 0, 0);
                    listOfRect[0] = sf::RectangleShape();
                }
            }
            else if(event.key.code == sf::Keyboard::B)
            {
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && totPlayer > 1)
                {
                    playerForRect = BLUE;
                    rectForPlayerPlace[1] = sf::IntRect(-1, -1, 0, 0);
                    listOfRect[1] = sf::RectangleShape();
                }
            }
            else if(event.key.code == sf::Keyboard::M)
            {
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && totPlayer > 2)
                {
                    playerForRect = MAGENTA;
                    rectForPlayerPlace[2] = sf::IntRect(-1, -1, 0, 0);
                    listOfRect[2] = sf::RectangleShape();
                }
            }
            else if(event.key.code == sf::Keyboard::C)
            {
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && totPlayer > 3)
                {
                    playerForRect = CYAN;
                    rectForPlayerPlace[3] = sf::IntRect(-1, -1, 0, 0);
                    listOfRect[3] = sf::RectangleShape();
                }
            }
        }
    }


    if(playerForRect == NO_PLAYER)
    {
        if(tmpWall.firstPoint.x != -1)
        {
            setSpriteForTmpWall();
        }
    }
    else
    {
        if(rectForPlayerPlace[playerForRect].left != -1)
        {
            listOfRect[playerForRect] = staticTray.creatRectPlaceFor(playerForRect, rectForPlayerPlace[playerForRect]);
        }
    }

    myWidgetManager.update();
    if(widgetManagerForTextIsActive == true)
    {
        widgetManagerForText.update();
    }
}

void editLevelClass::draw()
{
    global::window.clear(sf::Color::White);
    staticTray.draw();
    if(tmpWall.firstPoint.x != -1)
    {
        global::window.draw(tmpWall.sprite);
    }
    if(drawRect == true)
    {
        for(sf::RectangleShape& it : listOfRect)
        {
            global::window.draw(it);
        }
    }
    myWidgetManager.draw();
    if(widgetManagerForTextIsActive == true)
    {
        widgetManagerForText.draw();
    }
}

void editLevelClass::updateTray()
{
    staticTray.caseSizeTray = sf::Vector2f(global::window.getSize().x / 2 / staticTray.sizeTray.x, global::window.getSize().y / staticTray.sizeTray.y);
    staticTray.bordSize = sf::Vector2f(0,0);
    if(staticTray.caseSizeTray.x > staticTray.caseSizeTray.y)
    {
        staticTray.bordSize.x = (staticTray.caseSizeTray.x - staticTray.caseSizeTray.y) * staticTray.sizeTray.x / 2;
        staticTray.caseSizeTray.x = staticTray.caseSizeTray.y;
    }
    else if(staticTray.caseSizeTray.x < staticTray.caseSizeTray.y)
    {
        staticTray.bordSize.y = (staticTray.caseSizeTray.y - staticTray.caseSizeTray.x) * staticTray.sizeTray.y / 2;
        staticTray.caseSizeTray.y = staticTray.caseSizeTray.x;
    }
}

void editLevelClass::setNewTray()
{
    totPlayer = strtol(textBoxNbPlayer->getMessage().c_str(), NULL, 10);
    if(strtol(textBoxWidth->getMessage().c_str(), NULL, 10) < 1)
    {
        textBoxWidth->setMessage("1");
    }
    if(strtol(textBoxHeight->getMessage().c_str(), NULL, 10) < 1)
    {
        textBoxHeight->setMessage("1");
    }
    if(totPlayer < 1)
    {
        textBoxNbPlayer->setMessage("1");
        totPlayer = 1;
    }
    else if(totPlayer > 4)
    {
        textBoxNbPlayer->setMessage("4");
        totPlayer = 4;
    }
    if(strtol(textBoxTotNb->getMessage().c_str(), NULL, 10) < 1)
    {
        textBoxTotNb->setMessage("1");
    }
    if(strtol(textBoxMoveTot->getMessage().c_str(), NULL, 10) < 1)
    {
        textBoxMoveTot->setMessage("1");
    }
    if(strtol(textBoxMoveNb->getMessage().c_str(), NULL, 10) < 1)
    {
        textBoxMoveNb->setMessage("1");
    }
    staticTray.sizeTray.x = strtol(textBoxWidth->getMessage().c_str(), NULL, 10);
    staticTray.sizeTray.y = strtol(textBoxHeight->getMessage().c_str(), NULL, 10);
    updateTray();
    for(std::vector<wall>::iterator it = staticTray.listOfWall.begin(); it != staticTray.listOfWall.end(); )
    {
        if(it->firstPoint.x > staticTray.sizeTray.x || it->firstPoint.y > staticTray.sizeTray.y || it->firstPoint.x < 0 || it->firstPoint.y < 0 || it->secondPoint.x > staticTray.sizeTray.x || it->secondPoint.y > staticTray.sizeTray.y || it->secondPoint.x < 0 || it->secondPoint.y < 0)
        {
            it = staticTray.listOfWall.erase(it);
            continue;
        }
        ++it;
    }
    rectForPlayerPlace.resize(totPlayer);
    listOfRect.resize(totPlayer);
    for(size_t i = 0; i < listOfRect.size(); ++i)
    {
        if(rectForPlayerPlace[i].left >= staticTray.sizeTray.x || rectForPlayerPlace[i].top >= staticTray.sizeTray.y || rectForPlayerPlace[i].left < 0 || rectForPlayerPlace[i].top < 0 || rectForPlayerPlace[i].left + rectForPlayerPlace[i].width > staticTray.sizeTray.x || rectForPlayerPlace[i].top + rectForPlayerPlace[i].height > staticTray.sizeTray.y || rectForPlayerPlace[i].width < 0 || rectForPlayerPlace[i].height < 0)
        {
            listOfRect[i] = sf::RectangleShape();
        }
        else
        {
            listOfRect[i] = staticTray.creatRectPlaceFor(static_cast<typePlayer>(i), rectForPlayerPlace[i]);
        }
    }
    staticTray.updateWall();
    staticTray.createLine();
}

void editLevelClass::setSpriteForTmpWall()
{
    tmpWall.sprite.setFillColor(sf::Color::Black);
    tmpWall.sprite.setSize(sf::Vector2f((tmpWall.secondPoint.x - tmpWall.firstPoint.x) * staticTray.caseSizeTray.x + 2, (tmpWall.secondPoint.y - tmpWall.firstPoint.y) * staticTray.caseSizeTray.y + 2));
    tmpWall.sprite.setPosition(tmpWall.firstPoint.x * staticTray.caseSizeTray.x + staticTray.bordSize.x - 1, tmpWall.firstPoint.y * staticTray.caseSizeTray.y + staticTray.bordSize.y - 1);
}

void editLevelClass::loadLevel()
{
    int totalMoveForPlayer;
    int totalNumberForPlayer;
    int totalMoveForNumberForPlayer;
    int tmpTotPlayer;
    staticTrayClass tmpStaticTray;
    std::vector<sf::IntRect> vecRectForPlayerPlace;
    widgetManagerForTextIsActive = false;
    if(levelClass::loadLevel(textBoxWidgetForText->getMessage(), tmpTotPlayer, totalMoveForPlayer, totalNumberForPlayer, totalMoveForNumberForPlayer, vecRectForPlayerPlace, tmpStaticTray) == false)
    {
        return;
    }
    totPlayer = tmpTotPlayer;
    staticTray = tmpStaticTray;
    textBoxWidth->setMessage(intToStr(staticTray.sizeTray.x));
    textBoxHeight->setMessage(intToStr(staticTray.sizeTray.y));
    textBoxNbPlayer->setMessage(intToStr(totPlayer));
    textBoxTotNb->setMessage(intToStr(totalNumberForPlayer));
    textBoxMoveTot->setMessage(intToStr(totalMoveForPlayer));
    textBoxMoveNb->setMessage(intToStr(totalMoveForNumberForPlayer));
    rectForPlayerPlace.clear();
    for(sf::IntRect& rect : vecRectForPlayerPlace)
    {
        rectForPlayerPlace.push_back(rect);
    }
    setNewTray();
}

void editLevelClass::saveLevel()
{
    int totalMoveForPlayer;
    int totalNumberForPlayer;
    int totalMoveForNumberForPlayer;
    std::vector<sf::IntRect> vecRectForPlayerPlace;
    widgetManagerForTextIsActive = false;
    setNewTray();
    totalMoveForPlayer = strtol(textBoxMoveTot->getMessage().c_str(), NULL, 10);
    totalNumberForPlayer = strtol(textBoxTotNb->getMessage().c_str(), NULL, 10);
    totalMoveForNumberForPlayer = strtol(textBoxMoveNb->getMessage().c_str(), NULL, 10);
    for(sf::IntRect& rect : rectForPlayerPlace)
    {
        vecRectForPlayerPlace.push_back(rect);
    }
    levelClass::saveLevel(textBoxWidgetForText->getMessage(), totPlayer, totalMoveForPlayer, totalNumberForPlayer, totalMoveForNumberForPlayer, vecRectForPlayerPlace, staticTray);
}

std::string editLevelClass::intToStr(int thisInt)
{
    std::ostringstream oss;
    oss << thisInt;
    return oss.str();
}
