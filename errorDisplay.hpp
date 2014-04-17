#ifndef ERRORDISPLAY_HPP
#define ERRORDISPLAY_HPP

#include "structForGame.hpp"

class errorDisplayClass
{
public:
    bool getLineOf(std::string thisMessage, std::vector<point>& toThisVector);
    int getCharOf(char thisChar, std::vector<point>& toThisVector);
};

#endif
