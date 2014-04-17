#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include <SFML/Graphics.hpp>

class gameStateStackClass;

class gameStateClass
{
public:
	virtual ~gameStateClass() {};
	virtual void update() = 0;
	virtual void draw() = 0;
};

#endif
