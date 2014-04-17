#ifndef MAINMENUSTATE_HPP
#define MAINMENUSTATE_HPP

#include <memory>

#include "gameState.hpp"
#include "widgetManager.hpp"

#define TIME_FOR_KEY_PRESS 1
#define NUMBER_OF_KEY 10

class mainMenuStateClass : public gameStateClass
{
public:
    mainMenuStateClass();
    void update();
    void draw();
    void setMainMenu();
    void setLocalMenu();
    void setOnlineMenu();
    void setHostMenu();
    void playOffline();
    void playOnline();
    void hostServ();
    void setEditLevel();
    void setOption();
    void clearPtr();
private:
    widgetManagerClass myWidgetManager;
    std::string* onlineInfo;
    std::string* levelInfo;
    std::array<sf::Keyboard::Key, NUMBER_OF_KEY> secret;
    sf::Clock keyPressTime;
    int offset;
};

#endif
