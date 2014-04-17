#ifndef GAMESTATESTACK_HPP
#define GAMESTATESTACK_HPP

#include <SFML/Graphics.hpp>
#include <list>
#include <memory>

#include "gameState.hpp"

class gameStateStackClass
{
public:
	void set(gameStateClass* state);
	void add(gameStateClass* state);
	void pop();
	void clear();
	void update();
	void draw();
	void drawOld();
	bool getChange();
	void setChange(bool val);
private:
	std::list<std::unique_ptr<gameStateClass>> stateList;
	bool change;
};

#endif
