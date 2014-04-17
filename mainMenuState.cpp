#include "mainMenuState.hpp"
#include "textWidget.hpp"
#include "buttonWidget.hpp"
#include "widgetList.hpp"
#include "widgetTextBox.hpp"
#include "playState.hpp"
#include "internalServer.hpp"
#include "externalServer.hpp"
#include "serverState.hpp"
#include "optionState.hpp"
#include "editLevelStat.hpp"
#include "errorManager.hpp"
#include "global.hpp"

mainMenuStateClass::mainMenuStateClass()
{
    offset = 0;
    secret[0] = sf::Keyboard::Up;
    secret[1] = sf::Keyboard::Up;
    secret[2] = sf::Keyboard::Down;
    secret[3] = sf::Keyboard::Down;
    secret[4] = sf::Keyboard::Left;
    secret[5] = sf::Keyboard::Right;
    secret[6] = sf::Keyboard::Left;
    secret[7] = sf::Keyboard::Right;
    secret[8] = sf::Keyboard::B;
    secret[9] = sf::Keyboard::A;
    clearPtr();
    myWidgetManager.setLimit(sf::IntRect(0, 0, global::window.getSize().x, global::window.getSize().y));
    setMainMenu();
    keyPressTime.restart();
}

void mainMenuStateClass::update()
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
            myWidgetManager.mouseClick(event.mouseButton.x, event.mouseButton.y);
        }
        else if(event.type == sf::Event::MouseMoved)
        {
            myWidgetManager.mouseMove(event.mouseMove.x, event.mouseMove.y);
        }
        else if(event.type == sf::Event::TextEntered)
        {
            if(event.text.unicode < 128)
            {
                myWidgetManager.textIsEntered(static_cast<char>(event.text.unicode));
            }
        }
        else if(event.type == sf::Event::KeyPressed)
        {
            if(secret[offset] != event.key.code)
            {
                offset = 0;
            }
            if(secret[offset] == event.key.code)
            {
                ++offset;
                if(offset == NUMBER_OF_KEY)
                {
                    global::gameStateStack.set(new errorManagerClass);
                    return;
                }
            }
            keyPressTime.restart();
        }

        if(global::gameStateStack.getChange() == true)
        {
            return;
        }
    }

    if(keyPressTime.getElapsedTime().asSeconds() > TIME_FOR_KEY_PRESS)
    {
        offset = 0;
        keyPressTime.restart();
    }

    myWidgetManager.update();
}

void mainMenuStateClass::draw()
{
    global::window.clear(sf::Color::White);
    myWidgetManager.draw();
}

void mainMenuStateClass::setMainMenu()
{
    clearPtr();
    myWidgetManager.setWidgetHere(new textWidgetClass("Red Versus Blue: Attack"), TOP_LEFT, 10, 10);

    myWidgetManager.addToTmpList(new buttonWidgetClass("Jouer en local", std::bind(&mainMenuStateClass::setLocalMenu, this)));
    myWidgetManager.addToTmpList(new buttonWidgetClass("Jouer en réseau", std::bind(&mainMenuStateClass::setOnlineMenu, this)));
    myWidgetManager.addToTmpList(new buttonWidgetClass("Héberger un serveur", std::bind(&mainMenuStateClass::setHostMenu, this)));
    myWidgetManager.addToTmpList(new buttonWidgetClass("Editer un niveau", std::bind(&mainMenuStateClass::setEditLevel, this)));
    myWidgetManager.addToTmpList(new buttonWidgetClass("Option", std::bind(&mainMenuStateClass::setOption, this)));
    myWidgetManager.addToTmpList(new buttonWidgetClass("Quitter", std::bind(&sf::RenderWindow::close, &global::window)));
    myWidgetManager.setWidgetHere(myWidgetManager.createList(VERTICAL, MIDDLE, 5), MIDDLE_MIDDLE);
}

void mainMenuStateClass::setLocalMenu()
{
    widgetTextBox* myTextBox = new widgetTextBox("level.txt", "WWWWWWWWWWgWWWWWWWW|", STRING);
    widgetClass* myList;

    clearPtr();
    myTextBox->setPointerToText(levelInfo);
    myTextBox->setSlot(std::bind(&mainMenuStateClass::playOffline, this));

    myWidgetManager.addToTmpList(new buttonWidgetClass("Retour", std::bind(&mainMenuStateClass::setMainMenu, this)));
    myWidgetManager.addToTmpList(new buttonWidgetClass("Jouer", std::bind(&mainMenuStateClass::playOffline, this)));
    myList = myWidgetManager.createList(HORIZONTAL, MIDDLE, 50);

    myWidgetManager.addToTmpList(new textWidgetClass("Nom du niveau :"));
    myWidgetManager.addToTmpList(myTextBox);
    myWidgetManager.lastTmpWidgetHasFocus();
    myWidgetManager.addToTmpList(myList);
    myWidgetManager.setWidgetHere(myWidgetManager.createList(VERTICAL, MIDDLE, 25), MIDDLE_MIDDLE);
}

void mainMenuStateClass::setOnlineMenu()
{
    widgetTextBox* myTextBox = new widgetTextBox("", "WWWWWWWWWWWWgWWWWWWWWWWW|", STRING);
    widgetClass* myList;

    clearPtr();
    myTextBox->setPointerToText(onlineInfo);
    myTextBox->setSlot(std::bind(&mainMenuStateClass::playOnline, this));

    myWidgetManager.addToTmpList(new buttonWidgetClass("Retour", std::bind(&mainMenuStateClass::setMainMenu, this)));
    myWidgetManager.addToTmpList(new buttonWidgetClass("Jouer", std::bind(&mainMenuStateClass::playOnline, this)));
    myList = myWidgetManager.createList(HORIZONTAL, MIDDLE, 50);

    myWidgetManager.addToTmpList(new textWidgetClass("Ip du serveur :"));
    myWidgetManager.addToTmpList(myTextBox);
    myWidgetManager.lastTmpWidgetHasFocus();
    myWidgetManager.addToTmpList(myList);
    myWidgetManager.setWidgetHere(myWidgetManager.createList(VERTICAL, MIDDLE, 25), MIDDLE_MIDDLE);
}

void mainMenuStateClass::setHostMenu()
{
    widgetTextBox* textBoxLevel = new widgetTextBox("level.txt", "WWWWWWWWWWgWWWWWWWW|", STRING);
    widgetTextBox* textBoxPort = new widgetTextBox("8888", "WWWWW|", INT);
    widgetClass* myList;

    clearPtr();
    textBoxLevel->setPointerToText(levelInfo);
    textBoxLevel->setSlot(std::bind(&mainMenuStateClass::hostServ, this));
    textBoxPort->setPointerToText(onlineInfo);
    textBoxPort->setSlot(std::bind(&mainMenuStateClass::hostServ, this));

    myWidgetManager.addToTmpList(new buttonWidgetClass("Retour", std::bind(&mainMenuStateClass::setMainMenu, this)));
    myWidgetManager.addToTmpList(new buttonWidgetClass("Démarrer", std::bind(&mainMenuStateClass::hostServ, this)));
    myList = myWidgetManager.createList(HORIZONTAL, MIDDLE, 50);

    myWidgetManager.addToTmpList(new textWidgetClass("Nom du niveau :"));
    myWidgetManager.addToTmpList(textBoxLevel);
    myWidgetManager.lastTmpWidgetHasFocus();
    myWidgetManager.addToTmpList(new textWidgetClass("Port du serveur :"));
    myWidgetManager.addToTmpList(textBoxPort);
    myWidgetManager.addToTmpList(myList);
    myWidgetManager.setWidgetHere(myWidgetManager.createList(VERTICAL, MIDDLE, 25), MIDDLE_MIDDLE);
}

void mainMenuStateClass::playOffline()
{
    if(levelInfo != nullptr)
    {
        global::gameStateStack.set(new playStateClass(new internalServerClass(*levelInfo)));
    }
}

void mainMenuStateClass::playOnline()
{
    if(onlineInfo != nullptr)
    {
        std::string adress = *onlineInfo;
        std::string ipToCo = adress;
        int port = 8888;
        if(adress.find(':') != std::string::npos)
        {
            ipToCo = adress.substr(0, adress.find(':'));
            if(adress.size() - ipToCo.size() > 1)
            {
                adress.erase(0, adress.find(':') + 1);
                port = strtol(adress.c_str(), NULL, 10);
            }
        }
        global::gameStateStack.set(new playStateClass(new externalServerClass(ipToCo, port)));
    }
}

void mainMenuStateClass::hostServ()
{
    if(levelInfo != nullptr && onlineInfo != nullptr)
    {
        global::gameStateStack.set(new serverStateClass(strtol(onlineInfo->c_str(), NULL, 10), *levelInfo));
    }
}

void mainMenuStateClass::setEditLevel()
{
    global::gameStateStack.set(new editLevelClass);
}

void mainMenuStateClass::setOption()
{
    global::gameStateStack.set(new optionStateClass);
}

void mainMenuStateClass::clearPtr()
{
    myWidgetManager.clearAll();
    onlineInfo = nullptr;
    levelInfo = nullptr;
}
