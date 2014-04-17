#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>

#include "gameStateStack.hpp"
#include "soundManager.hpp"

class gameClass
{
public:
	gameClass();
	void run();
private:
	sf::Clock time;
	soundManagerClass soundManager;
};

#endif
