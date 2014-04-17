#include <sstream>
#include <fstream>

#include "optionState.hpp"
#include "widgetTextBox.hpp"
#include "widgetList.hpp"
#include "buttonWidget.hpp"
#include "mainMenuState.hpp"

optionStateClass::optionStateClass()
{
    widgetClass* myListOfTextBox;
    widgetClass* myListOfResizeButton;
    widgetClass* myListOfButton;
    widgetClass* myListVertical;
    widgetClass* myListForFullScreen;
    widgetClass* myListForRatio;
    widgetClass* myListForSound;

    maximumHeight = sf::VideoMode::getDesktopMode().height;
    textBoxWidth = new widgetTextBox("", "lWWW", INT);
    textBoxHeight = new widgetTextBox("", "lWWW", INT);
    fullScreen = new buttonWidgetClass((global::isFullScreen ? "activé" : "désactivé"), std::bind(&optionStateClass::setIsFullScreen, this));
    fourThirds = new buttonWidgetClass((global::isFourThirds ? "4/3" : "16/9"), std::bind(&optionStateClass::setIsFourThirds, this));
    switch(global::soundType)
    {
        case ALL:
        {
            sound = new buttonWidgetClass("tous", std::bind(&optionStateClass::setTypeSound, this));
            break;
        }
        case END_TURN_ONLY:
        {
            sound = new buttonWidgetClass("fin de tour uniquement", std::bind(&optionStateClass::setTypeSound, this));
            break;
        }
        case NEVER:
        {
            sound = new buttonWidgetClass("aucun", std::bind(&optionStateClass::setTypeSound, this));
            break;
        }
        default:
        {
            sound = new buttonWidgetClass("tous", std::bind(&optionStateClass::setTypeSound, this));
            break;
        }
    }
    myWidgetManager.setLimit(sf::IntRect(0, 0, global::window.getSize().x, global::window.getSize().y));

    if(global::isFourThirds == true)
    {
        ratioScreenSize.x = 40;
        ratioScreenSize.y = 30;
    }
    else
    {
        ratioScreenSize.x = 80;
        ratioScreenSize.y = 45;
    }

    textBoxWidth->setMessage(intToStr(global::sizeWindow.x));
    textBoxWidth->setIsReadOnly(true);

    textBoxHeight->setMessage(intToStr(global::sizeWindow.y));
    textBoxHeight->setIsReadOnly(true);

    myWidgetManager.addToTmpList(textBoxWidth);
    myWidgetManager.addToTmpList(new textWidgetClass("x"));
    myWidgetManager.addToTmpList(textBoxHeight);
    myListOfTextBox = myWidgetManager.createList(HORIZONTAL, MIDDLE, 5);

    myWidgetManager.addToTmpList(new buttonWidgetClass("<", std::bind(&optionStateClass::decreaseSizeWindow, this)));
    myWidgetManager.addToTmpList(new buttonWidgetClass(">", std::bind(&optionStateClass::increaseSizeWindow, this)));
    myListOfResizeButton = myWidgetManager.createList(HORIZONTAL, MIDDLE, 50);

    myWidgetManager.addToTmpList(new textWidgetClass("Ratio : "));
    myWidgetManager.addToTmpList(fourThirds);
    myListForRatio = myWidgetManager.createList(HORIZONTAL, MIDDLE, 10);

    myWidgetManager.addToTmpList(new textWidgetClass("Plein écran : "));
    myWidgetManager.addToTmpList(fullScreen);
    myListForFullScreen = myWidgetManager.createList(HORIZONTAL, MIDDLE, 10);

    myWidgetManager.addToTmpList(new textWidgetClass("Son : "));
    myWidgetManager.addToTmpList(sound);
    myListForSound = myWidgetManager.createList(HORIZONTAL, MIDDLE, 10);

    myWidgetManager.addToTmpList(new buttonWidgetClass("Retour", std::bind(&optionStateClass::setMainMenu, this)));
    myWidgetManager.addToTmpList(new buttonWidgetClass("Accepter", std::bind(&optionStateClass::setNewSizeWindow, this)));
    myListOfButton = myWidgetManager.createList(HORIZONTAL, MIDDLE, 50);

    myWidgetManager.addToTmpList(myListOfTextBox);
    myWidgetManager.addToTmpList(myListOfResizeButton);
    myWidgetManager.addToTmpList(myListForRatio);
    myWidgetManager.addToTmpList(myListForFullScreen);
    myWidgetManager.addToTmpList(myListForSound);
    myWidgetManager.addToTmpList(myListOfButton);
    myListVertical = myWidgetManager.createList(VERTICAL, MIDDLE, 5);

    myWidgetManager.addToTmpList(new textWidgetClass("Résolution :"));
    myWidgetManager.addToTmpList(myListVertical);
    myWidgetManager.setWidgetHere(myWidgetManager.createList(VERTICAL, MIDDLE, 25), MIDDLE_MIDDLE);
}

void optionStateClass::update()
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

        if(global::gameStateStack.getChange() == true)
        {
            return;
        }
    }

    myWidgetManager.update();
}

void optionStateClass::draw()
{
    global::window.clear(sf::Color::White);
    myWidgetManager.draw();
}

void optionStateClass::increaseSizeWindow()
{
    global::sizeWindow.x += ratioScreenSize.x;
    global::sizeWindow.y += ratioScreenSize.y;
    if(global::sizeWindow.y > maximumHeight)
    {
        global::sizeWindow.x -= ratioScreenSize.x;
        global::sizeWindow.y -= ratioScreenSize.y;
    }
    textBoxWidth->setMessage(intToStr(global::sizeWindow.x));
    textBoxHeight->setMessage(intToStr(global::sizeWindow.y));
}

void optionStateClass::decreaseSizeWindow()
{
    global::sizeWindow.x -= ratioScreenSize.x;
    global::sizeWindow.y -= ratioScreenSize.y;
    if(global::sizeWindow.y < 480)
    {
        global::sizeWindow.x += ratioScreenSize.x;
        global::sizeWindow.y += ratioScreenSize.y;
    }
    textBoxWidth->setMessage(intToStr(global::sizeWindow.x));
    textBoxHeight->setMessage(intToStr(global::sizeWindow.y));
}

void optionStateClass::setIsFullScreen()
{
    global::isFullScreen = !global::isFullScreen;

    if(global::isFullScreen == true)
    {
        global::sizeWindow.x = sf::VideoMode::getDesktopMode().width;
        global::sizeWindow.y = sf::VideoMode::getDesktopMode().height;
        fullScreen->setMessage("activé");
    }
    else
    {
        fullScreen->setMessage("désactivé");
    }

    myWidgetManager.widgetHasChanged();
}

void optionStateClass::setIsFourThirds()
{
    global::isFourThirds = !global::isFourThirds;

    if(global::isFourThirds == true)
    {
        global::sizeWindow.x = 960;
        global::sizeWindow.y = 720;
        ratioScreenSize.x = 40;
        ratioScreenSize.y = 30;
        fourThirds->setMessage("4/3");
    }
    else
    {
        global::sizeWindow.x = 1280;
        global::sizeWindow.y = 720;
        ratioScreenSize.x = 80;
        ratioScreenSize.y = 45;
        fourThirds->setMessage("16/9");
    }
    textBoxWidth->setMessage(intToStr(global::sizeWindow.x));
    textBoxHeight->setMessage(intToStr(global::sizeWindow.y));

    myWidgetManager.widgetHasChanged();
}

void optionStateClass::setTypeSound()
{
    global::soundType = static_cast<typeSound>((static_cast<int>(global::soundType) + 1) % 3);
    switch(global::soundType)
    {
        case ALL:
        {
            sound->setMessage("tous");
            break;
        }
        case END_TURN_ONLY:
        {
            sound->setMessage("fin de tour uniquement");
            break;
        }
        case NEVER:
        {
            sound->setMessage("aucun");
            break;
        }
        default:
        {
            sound->setMessage("tous");
            break;
        }
    }
    myWidgetManager.widgetHasChanged();
}

void optionStateClass::setMainMenu()
{
    global::gameStateStack.set(new mainMenuStateClass);
}

void optionStateClass::setNewSizeWindow()
{
    saveOption();
    adaptSizeChar();
	global::window.create(sf::VideoMode(global::sizeWindow.x, global::sizeWindow.y), global::windowName, sf::Style::Titlebar | sf::Style::Close | (global::isFullScreen ? sf::Style::Fullscreen : sf::Style::None));
    global::gameStateStack.set(new optionStateClass);
}

void optionStateClass::saveOption()
{
    std::ofstream file("conf.txt");
    if(file.is_open())
    {
        file << global::sizeWindow.x << std::endl;
        file << global::sizeWindow.y << std::endl;
        file << global::isFourThirds << std::endl;
        file << global::isFullScreen << std::endl;
        file << global::soundType << std::endl;
    }
    file.close();
}

void optionStateClass::loadOption()
{
    unsigned int tmpSizeX;
    unsigned int tmpSizeY;
    bool tmpFourthThirds;
    bool tmpFullScreen;
    int tmpSound;
    bool fail = false;
    std::ifstream file("conf.txt");
    if(file.is_open())
    {
        if(!(file >> tmpSizeX))
        {
            fail = true;
        }
        if(!(file >> tmpSizeY))
        {
            fail = true;
        }
        if(!(file >> tmpFourthThirds))
        {
            fail = true;
        }
        if(!(file >> tmpFullScreen))
        {
            fail = true;
        }
        if(!(file >> tmpSound))
        {
            fail = true;
        }
    }
    file.close();

    if(tmpSizeX < 640 || tmpSizeY < 480 || tmpSizeX > sf::VideoMode::getDesktopMode().width || tmpSizeY > sf::VideoMode::getDesktopMode().height || tmpSound < 0 || tmpSound > 2)
    {
        fail = true;
    }

    if(fail == false)
    {
        global::sizeWindow.x = tmpSizeX;
        global::sizeWindow.y = tmpSizeY;
        global::isFourThirds = tmpFourthThirds;
        global::isFullScreen = tmpFullScreen;
        global::soundType = static_cast<typeSound>(tmpSound);
    }

    adaptSizeChar();
}

void optionStateClass::adaptSizeChar()
{
    double windowRatio = global::sizeWindow.x / static_cast<double>(global::sizeWindow.y);
    if(windowRatio < 1.5)
    {
        global::sizeChar = ((global::sizeWindow.y - 480) / 28) + 22;
    }
    else
    {
        global::sizeChar = ((global::sizeWindow.y - 495) / 20) + 25;
    }
}

std::string optionStateClass::intToStr(int thisInt)
{
    std::ostringstream oss;
    oss << thisInt;
    return oss.str();
}
