#ifndef ERRORMANAGER_HPP
#define ERRORMANAGER_HPP

#include <map>
#include <list>

#include "gameState.hpp"
#include "staticTray.hpp"
#include "caseType.hpp"
#include "errorDisplay.hpp"
#include "structForGame.hpp"

class errorManagerClass : public gameStateClass
{
public:
    errorManagerClass();
    ~errorManagerClass();
    void update();
    void draw();
    void setCredit();
    void setTrayForCredit();
    void creatRandomCaseAt(point thisPos, bool withOutlineTickness = true);
private:
    errorDisplayClass errorDisplay;
    staticTrayClass staticTray;
    std::map<point, caseTypeClass> tray;
    point lastCase;
    sf::Vector2f oldMousePos;
    std::minstd_rand random;
    bool isCredit;
    bool trayCreditIsSet;
    std::list<std::string> creditMessages;
    int numOfLine;
    bool timeLineIsRunning;
    bool timeMessageIsRunning;
    bool waitKill;
    sf::Clock timeLine;
    sf::Clock timeMessage;
    typeSound currentTypeSound;
};

#endif
