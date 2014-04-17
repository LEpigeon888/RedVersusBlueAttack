#ifndef GLOBAL_HPP
#define GLOBAL_HPP

#include <SFML/Graphics.hpp>

#include "gameStateStack.hpp"
#include "typeForGame.hpp"

class soundManagerClass;

struct global
{
    static double timeFrame;
	static sf::RenderWindow window;
	static gameStateStackClass gameStateStack;
	static sf::Color grey;
	static sf::Font font;
    static sf::Vector2u sizeWindow;
    static bool isFullScreen;
    static bool isFourThirds;
    static int sizeChar;
    static typeSound soundType;
    static soundManagerClass* soundManager;
    static bool run;
    static std::string windowName;
};

#endif
