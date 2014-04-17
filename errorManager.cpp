#include <random>
#include <chrono>
#include <fstream>

#include "errorManager.hpp"
#include "mainMenuState.hpp"
#include "global.hpp"

errorManagerClass::errorManagerClass()
{
    oldMousePos.x = -1;
    numOfLine = 0;
    isCredit = false;
    trayCreditIsSet = false;
    timeLineIsRunning = false;
    timeMessageIsRunning = false;
    waitKill = false;
    random.seed(std::chrono::system_clock::now().time_since_epoch().count());
    staticTray.setTakeHalfScreen(false);
    staticTray.sizeTray.x = static_cast<int>(global::window.getSize().x / 30);
    staticTray.sizeTray.y = static_cast<int>(global::window.getSize().y / 30);
    staticTray.caseSizeTray = sf::Vector2f(global::window.getSize().x / staticTray.sizeTray.x, global::window.getSize().y / staticTray.sizeTray.y);
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
    staticTray.createLine();
}

errorManagerClass::~errorManagerClass()
{
    global::soundType = currentTypeSound;
}

void errorManagerClass::update()
{
    sf::Event event;
    while(global::window.pollEvent(event))
    {
        if(event.type == sf::Event::Closed)
        {
            global::run = false;
        }
        else if(event.type == sf::Event::MouseMoved)
        {
            if(isCredit == false)
            {
                int x = event.mouseMove.x;
                int y = event.mouseMove.y;
                if(x > staticTray.bordSize.x && x < global::window.getSize().x - staticTray.bordSize.x && y > staticTray.bordSize.y && y < global::window.getSize().y - staticTray.bordSize.y)
                {
                    x = (x - staticTray.bordSize.x) / staticTray.caseSizeTray.x;
                    y = (y - staticTray.bordSize.y) / staticTray.caseSizeTray.y;
                    if(oldMousePos.x != x || oldMousePos.y != y)
                    {
                        creatRandomCaseAt(point(x, y));
                        oldMousePos.x = x;
                        oldMousePos.y = y;
                    }
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
            if(event.key.code == sf::Keyboard::Space)
            {
                if(timeMessageIsRunning == true && waitKill == false)
                {
                    for(auto& it : tray)
                    {
                        it.second.kill();
                    }
                    waitKill = true;
                }
            }
        }
    }

    if(isCredit == true && trayCreditIsSet == true)
    {
        if(timeLineIsRunning == false && timeMessageIsRunning == false)
        {
            std::vector<point> tmpVec;

            if(creditMessages.empty() == true)
            {
                global::gameStateStack.set(new mainMenuStateClass);
                return;
            }

            if(creditMessages.front() == "@")
            {
                creditMessages.pop_front();
                ++numOfLine;
            }
            else if(creditMessages.front() == "")
            {
                creditMessages.pop_front();
                timeMessageIsRunning = true;
                numOfLine = 0;
                timeMessage.restart();
            }
            else
            {
                errorDisplay.getLineOf(creditMessages.front(), tmpVec);

                for(point thisPoint : tmpVec)
                {
                    creatRandomCaseAt(point(thisPoint.first, thisPoint.second + (7 * numOfLine)), false);
                }

                creditMessages.pop_front();
                timeLineIsRunning = true;
                ++numOfLine;
                timeLine.restart();
            }
        }

        if(timeLineIsRunning == true && timeLine.getElapsedTime().asSeconds() > 0.1)
        {
            timeLineIsRunning = false;
        }
        if(timeMessageIsRunning == true && waitKill == false && timeMessage.getElapsedTime().asSeconds() > 60)
        {
            for(auto& it : tray)
            {
                it.second.kill();
            }
            waitKill = true;
        }
    }

    for(auto& caseTray : tray)
    {
        caseTray.second.update();
    }

    if(isCredit == false)
    {
        if(tray.size() >= staticTray.sizeTray.x * staticTray.sizeTray.y)
        {
            std::map<point, caseTypeClass>::iterator tmpIt = tray.find(lastCase);
            if(tmpIt != tray.end())
            {
                if(tmpIt->second.getIsPlain() == true)
                {
                    setCredit();
                }
            }
        }
    }

    if(tray.size() > 0)
    {
        std::map<point, caseTypeClass>::iterator tmpIt = tray.find(lastCase);
        if(tmpIt != tray.end())
        {
            if(tmpIt->second.getIsKilled() == true)
            {
                tray.clear();
                if(isCredit == true && trayCreditIsSet == false)
                {
                    setTrayForCredit();
                }
                else if(isCredit == true && trayCreditIsSet == true)
                {
                    timeLineIsRunning = false;
                    timeMessageIsRunning = false;
                }
                waitKill = false;
            }
        }
    }
}

void errorManagerClass::draw()
{
    global::window.clear(sf::Color::White);
    for(auto& it : tray)
    {
        global::window.draw(it.second.sprite());
    }
    staticTray.draw();
}

void errorManagerClass::setCredit()
{
    isCredit = true;
    for(auto& it : tray)
    {
        it.second.kill();
    }
    currentTypeSound = global::soundType;
    global::soundType = NEVER;
    creditMessages.push_back("@");
    creditMessages.push_back("@");
    creditMessages.push_back("@");
    creditMessages.push_back("          Bien joue !");
    creditMessages.push_back("");
    creditMessages.push_back("@");
    creditMessages.push_back("Enfin, c'etait pas");
    creditMessages.push_back("non plus super dur,");
    creditMessages.push_back("mais c'etait long,");
    creditMessages.push_back("surtout pour les");
    creditMessages.push_back("grosses resolutions.");
    creditMessages.push_back("");
    creditMessages.push_back("@");
    creditMessages.push_back("@");
    creditMessages.push_back("Bon, si tu t'attendais");
    creditMessages.push_back("a quelque chose");
    creditMessages.push_back("d'epique bah c'est");
    creditMessages.push_back("rate.");
    creditMessages.push_back("");
    creditMessages.push_back("Puis moi aussi ca m'a");
    creditMessages.push_back("prit du temps, les");
    creditMessages.push_back("lettres c'etait");
    creditMessages.push_back("chiant a faire, puis");
    creditMessages.push_back("en plus certaines");
    creditMessages.push_back("sont bien moche,");
    creditMessages.push_back("comme le w ou le m par");
    creditMessages.push_back("exemple.");
    creditMessages.push_back("");
    creditMessages.push_back("@");
    creditMessages.push_back("Et le resultat est");
    creditMessages.push_back("limite illisible des");
    creditMessages.push_back("fois, surtout quand");
    creditMessages.push_back("on lit avec une");
    creditMessages.push_back("petite resolution...");
    creditMessages.push_back("");
    creditMessages.push_back("@");
    creditMessages.push_back("Enfin bref, osef.");
    creditMessages.push_back("Il y a plein de");
    creditMessages.push_back("couleurs partout");
    creditMessages.push_back("c'est swag, c'est");
    creditMessages.push_back("cool.");
    creditMessages.push_back("");
    creditMessages.push_back("Ah, et une derniere");
    creditMessages.push_back("chose, si t'as trouve");
    creditMessages.push_back("ca en regardant le");
    creditMessages.push_back("code source, donc");
    creditMessages.push_back("en trichant, t'as");
    creditMessages.push_back("aucun merite.");
    creditMessages.push_back("@");
    creditMessages.push_back("POWNED");
    creditMessages.push_back("");
    creditMessages.push_back("@");
    creditMessages.push_back("@");
    creditMessages.push_back("Ceci est un message");
    creditMessages.push_back("cache inutile, galere");
    creditMessages.push_back("bien pour le lire.");
}

void errorManagerClass::setTrayForCredit()
{
    trayCreditIsSet = true;
    staticTray.sizeTray.x = 80;
    staticTray.sizeTray.y = 60;
    staticTray.caseSizeTray = sf::Vector2f(global::window.getSize().x / staticTray.sizeTray.x, global::window.getSize().y / staticTray.sizeTray.y);
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
    staticTray.createLine();
}

void errorManagerClass::creatRandomCaseAt(point thisPos, bool withOutlineTickness)
{
    if(tray.find(thisPos) == tray.end())
    {
        tray[thisPos] = caseTypeClass(static_cast<typePlayer>(random() % 4), ((random() % 2) == 1) && withOutlineTickness, random() % 3, sf::Vector2f(thisPos.first, thisPos.second), staticTray.caseSizeTray, staticTray.bordSize, ((random() % 2) == 1) && withOutlineTickness);
        lastCase = thisPos;
    }
}
