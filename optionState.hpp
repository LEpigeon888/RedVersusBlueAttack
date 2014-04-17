#ifndef OPTIONSTATE_HPP
#define OPTIONSTATE_HPP

#include "gameState.hpp"
#include "widgetManager.hpp"

class widgetTextBox;
class buttonWidgetClass;

class optionStateClass : public gameStateClass
{
public:
    optionStateClass();
    void update();
    void draw();
    void increaseSizeWindow();
    void decreaseSizeWindow();
    void setIsFullScreen();
    void setIsFourThirds();
    void setTypeSound();
    void setMainMenu();
    void setNewSizeWindow();
    void saveOption();
    static void adaptSizeChar();
    static void loadOption();
    std::string intToStr(int thisInt);
private:
    sf::Vector2u ratioScreenSize;
    widgetManagerClass myWidgetManager;
    unsigned int maximumHeight;
    widgetTextBox* textBoxWidth;
    widgetTextBox* textBoxHeight;
    buttonWidgetClass* fullScreen;
    buttonWidgetClass* fourThirds;
    buttonWidgetClass* sound;
};

#endif
