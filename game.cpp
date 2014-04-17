#include "game.hpp"
#include "mainMenuState.hpp"
#include "optionState.hpp"
#include "global.hpp"

gameClass::gameClass()
{
    global::font.loadFromFile("cour.ttf");
    optionStateClass::loadOption();
    soundManager.loadSound();
    global::soundManager = &soundManager;
	global::window.create(sf::VideoMode(global::sizeWindow.x, global::sizeWindow.y), global::windowName, sf::Style::Titlebar | sf::Style::Close | (global::isFullScreen ? sf::Style::Fullscreen : sf::Style::None));
	global::window.setFramerateLimit(60);
	global::gameStateStack.set(new mainMenuStateClass());
	global::timeFrame = 1. / 60.;
}

void gameClass::run()
{
	while(global::window.isOpen() && global::run == true)
	{
		time.restart();
		global::gameStateStack.update();
		while(global::gameStateStack.getChange())
		{
			global::gameStateStack.setChange(false);
			global::gameStateStack.update();
		}
        global::gameStateStack.draw();
		global::window.display();
		global::timeFrame = time.getElapsedTime().asSeconds();
	}
	global::gameStateStack.clear();
}
