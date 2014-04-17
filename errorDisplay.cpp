#include <memory>

#include "errorDisplay.hpp"

bool errorDisplayClass::getLineOf(std::string thisMessage, std::vector<point>& toThisVector)
{
    int sizeMessage = 0;

    for(char thisChar : thisMessage)
    {
        int tmpSize = 0;
        std::vector<point> tmpVec;

        tmpSize = getCharOf(thisChar, tmpVec);

        for(point thisPoint : tmpVec)
        {
            toThisVector.push_back(point(thisPoint.first + sizeMessage, thisPoint.second));
        }

        sizeMessage += tmpSize + 1;
    }
    --sizeMessage;

    if(sizeMessage > 64)
    {
        return false;
    }

    return true;
}

int errorDisplayClass::getCharOf(char thisChar, std::vector<point>& toThisVector)
{
    int sizeChar = 0;
    switch(thisChar)
    {
        case 'a':
        case 'A':
        {
            toThisVector.push_back(point(0, 0));
            toThisVector.push_back(point(0, 1));
            toThisVector.push_back(point(0, 2));
            toThisVector.push_back(point(0, 3));
            toThisVector.push_back(point(0, 4));
            toThisVector.push_back(point(1, 0));
            toThisVector.push_back(point(1, 2));
            toThisVector.push_back(point(2, 0));
            toThisVector.push_back(point(2, 1));
            toThisVector.push_back(point(2, 2));
            toThisVector.push_back(point(2, 3));
            toThisVector.push_back(point(2, 4));
            sizeChar = 3;
            break;
        }
        case 'b':
        case 'B':
        {
            toThisVector.push_back(point(0, 0));
            toThisVector.push_back(point(0, 1));
            toThisVector.push_back(point(0, 2));
            toThisVector.push_back(point(0, 3));
            toThisVector.push_back(point(0, 4));
            toThisVector.push_back(point(1, 0));
            toThisVector.push_back(point(1, 2));
            toThisVector.push_back(point(1, 4));
            toThisVector.push_back(point(2, 0));
            toThisVector.push_back(point(2, 1));
            toThisVector.push_back(point(2, 3));
            toThisVector.push_back(point(2, 4));
            sizeChar = 3;
            break;
        }
        case 'c':
        case 'C':
        {
            toThisVector.push_back(point(0, 0));
            toThisVector.push_back(point(0, 1));
            toThisVector.push_back(point(0, 2));
            toThisVector.push_back(point(0, 3));
            toThisVector.push_back(point(0, 4));
            toThisVector.push_back(point(1, 0));
            toThisVector.push_back(point(1, 4));
            toThisVector.push_back(point(2, 0));
            toThisVector.push_back(point(2, 4));
            sizeChar = 3;
            break;
        }
        case 'd':
        case 'D':
        {
            toThisVector.push_back(point(0, 0));
            toThisVector.push_back(point(0, 1));
            toThisVector.push_back(point(0, 2));
            toThisVector.push_back(point(0, 3));
            toThisVector.push_back(point(0, 4));
            toThisVector.push_back(point(1, 0));
            toThisVector.push_back(point(1, 4));
            toThisVector.push_back(point(2, 1));
            toThisVector.push_back(point(2, 2));
            toThisVector.push_back(point(2, 3));
            sizeChar = 3;
            break;
        }
        case 'e':
        case 'E':
        {
            toThisVector.push_back(point(0, 0));
            toThisVector.push_back(point(0, 1));
            toThisVector.push_back(point(0, 2));
            toThisVector.push_back(point(0, 3));
            toThisVector.push_back(point(0, 4));
            toThisVector.push_back(point(1, 0));
            toThisVector.push_back(point(1, 2));
            toThisVector.push_back(point(1, 4));
            toThisVector.push_back(point(2, 0));
            toThisVector.push_back(point(2, 4));
            sizeChar = 3;
            break;
        }
        case 'f':
        case 'F':
        {
            toThisVector.push_back(point(0, 0));
            toThisVector.push_back(point(0, 1));
            toThisVector.push_back(point(0, 2));
            toThisVector.push_back(point(0, 3));
            toThisVector.push_back(point(0, 4));
            toThisVector.push_back(point(1, 0));
            toThisVector.push_back(point(1, 2));
            toThisVector.push_back(point(2, 0));
            sizeChar = 3;
            break;
        }
        case 'g':
        case 'G':
        {
            toThisVector.push_back(point(0, 0));
            toThisVector.push_back(point(0, 1));
            toThisVector.push_back(point(0, 2));
            toThisVector.push_back(point(0, 3));
            toThisVector.push_back(point(0, 4));
            toThisVector.push_back(point(1, 0));
            toThisVector.push_back(point(1, 4));
            toThisVector.push_back(point(2, 0));
            toThisVector.push_back(point(2, 2));
            toThisVector.push_back(point(2, 4));
            toThisVector.push_back(point(3, 0));
            toThisVector.push_back(point(3, 2));
            toThisVector.push_back(point(3, 3));
            toThisVector.push_back(point(3, 4));
            sizeChar = 4;
            break;
        }
        case 'h':
        case 'H':
        {
            toThisVector.push_back(point(0, 0));
            toThisVector.push_back(point(0, 1));
            toThisVector.push_back(point(0, 2));
            toThisVector.push_back(point(0, 3));
            toThisVector.push_back(point(0, 4));
            toThisVector.push_back(point(1, 2));
            toThisVector.push_back(point(2, 0));
            toThisVector.push_back(point(2, 1));
            toThisVector.push_back(point(2, 2));
            toThisVector.push_back(point(2, 3));
            toThisVector.push_back(point(2, 4));
            sizeChar = 3;
            break;
        }
        case 'i':
        case 'I':
        {
            toThisVector.push_back(point(0, 0));
            toThisVector.push_back(point(0, 4));
            toThisVector.push_back(point(1, 0));
            toThisVector.push_back(point(1, 1));
            toThisVector.push_back(point(1, 2));
            toThisVector.push_back(point(1, 3));
            toThisVector.push_back(point(1, 4));
            toThisVector.push_back(point(2, 0));
            toThisVector.push_back(point(2, 4));
            sizeChar = 3;
            break;
        }
        case 'j':
        case 'J':
        {
            toThisVector.push_back(point(0, 3));
            toThisVector.push_back(point(0, 4));
            toThisVector.push_back(point(1, 4));
            toThisVector.push_back(point(2, 0));
            toThisVector.push_back(point(2, 1));
            toThisVector.push_back(point(2, 2));
            toThisVector.push_back(point(2, 3));
            toThisVector.push_back(point(2, 4));
            sizeChar = 3;
            break;
        }
        case 'k':
        case 'K':
        {
            toThisVector.push_back(point(0, 0));
            toThisVector.push_back(point(0, 1));
            toThisVector.push_back(point(0, 2));
            toThisVector.push_back(point(0, 3));
            toThisVector.push_back(point(0, 4));
            toThisVector.push_back(point(1, 2));
            toThisVector.push_back(point(2, 0));
            toThisVector.push_back(point(2, 1));
            toThisVector.push_back(point(2, 3));
            toThisVector.push_back(point(2, 4));
            sizeChar = 3;
            break;
        }
        case 'l':
        case 'L':
        {
            toThisVector.push_back(point(0, 0));
            toThisVector.push_back(point(0, 1));
            toThisVector.push_back(point(0, 2));
            toThisVector.push_back(point(0, 3));
            toThisVector.push_back(point(0, 4));
            toThisVector.push_back(point(1, 4));
            toThisVector.push_back(point(2, 4));
            sizeChar = 3;
            break;
        }
        case 'm':
        case 'M':
        {
            toThisVector.push_back(point(0, 0));
            toThisVector.push_back(point(0, 1));
            toThisVector.push_back(point(0, 2));
            toThisVector.push_back(point(0, 3));
            toThisVector.push_back(point(0, 4));
            toThisVector.push_back(point(1, 1));
            toThisVector.push_back(point(2, 1));
            toThisVector.push_back(point(3, 0));
            toThisVector.push_back(point(3, 1));
            toThisVector.push_back(point(3, 2));
            toThisVector.push_back(point(3, 3));
            toThisVector.push_back(point(3, 4));
            sizeChar = 4;
            break;
        }
        case 'n':
        case 'N':
        {
            toThisVector.push_back(point(0, 0));
            toThisVector.push_back(point(0, 1));
            toThisVector.push_back(point(0, 2));
            toThisVector.push_back(point(0, 3));
            toThisVector.push_back(point(0, 4));
            toThisVector.push_back(point(1, 1));
            toThisVector.push_back(point(2, 2));
            toThisVector.push_back(point(3, 0));
            toThisVector.push_back(point(3, 1));
            toThisVector.push_back(point(3, 2));
            toThisVector.push_back(point(3, 3));
            toThisVector.push_back(point(3, 4));
            sizeChar = 4;
            break;
        }
        case 'o':
        case 'O':
        {
            toThisVector.push_back(point(0, 0));
            toThisVector.push_back(point(0, 1));
            toThisVector.push_back(point(0, 2));
            toThisVector.push_back(point(0, 3));
            toThisVector.push_back(point(0, 4));
            toThisVector.push_back(point(1, 0));
            toThisVector.push_back(point(1, 4));
            toThisVector.push_back(point(2, 0));
            toThisVector.push_back(point(2, 1));
            toThisVector.push_back(point(2, 2));
            toThisVector.push_back(point(2, 3));
            toThisVector.push_back(point(2, 4));
            sizeChar = 3;
            break;
        }
        case 'p':
        case 'P':
        {
            toThisVector.push_back(point(0, 0));
            toThisVector.push_back(point(0, 1));
            toThisVector.push_back(point(0, 2));
            toThisVector.push_back(point(0, 3));
            toThisVector.push_back(point(0, 4));
            toThisVector.push_back(point(1, 0));
            toThisVector.push_back(point(1, 2));
            toThisVector.push_back(point(2, 0));
            toThisVector.push_back(point(2, 1));
            toThisVector.push_back(point(2, 2));
            sizeChar = 3;
            break;
        }
        case 'q':
        case 'Q':
        {
            toThisVector.push_back(point(0, 0));
            toThisVector.push_back(point(0, 1));
            toThisVector.push_back(point(0, 2));
            toThisVector.push_back(point(0, 3));
            toThisVector.push_back(point(1, 0));
            toThisVector.push_back(point(1, 3));
            toThisVector.push_back(point(2, 0));
            toThisVector.push_back(point(2, 1));
            toThisVector.push_back(point(2, 2));
            toThisVector.push_back(point(2, 3));
            toThisVector.push_back(point(3, 4));
            sizeChar = 4;
            break;
        }
        case 'r':
        case 'R':
        {
            toThisVector.push_back(point(0, 0));
            toThisVector.push_back(point(0, 1));
            toThisVector.push_back(point(0, 2));
            toThisVector.push_back(point(0, 3));
            toThisVector.push_back(point(0, 4));
            toThisVector.push_back(point(1, 0));
            toThisVector.push_back(point(1, 2));
            toThisVector.push_back(point(1, 3));
            toThisVector.push_back(point(2, 0));
            toThisVector.push_back(point(2, 1));
            toThisVector.push_back(point(2, 2));
            toThisVector.push_back(point(2, 4));
            sizeChar = 3;
            break;
        }
        case 's':
        case 'S':
        {
            toThisVector.push_back(point(0, 0));
            toThisVector.push_back(point(0, 1));
            toThisVector.push_back(point(0, 2));
            toThisVector.push_back(point(0, 4));
            toThisVector.push_back(point(1, 0));
            toThisVector.push_back(point(1, 2));
            toThisVector.push_back(point(1, 4));
            toThisVector.push_back(point(2, 0));
            toThisVector.push_back(point(2, 2));
            toThisVector.push_back(point(2, 3));
            toThisVector.push_back(point(2, 4));
            sizeChar = 3;
            break;
        }
        case 't':
        case 'T':
        {
            toThisVector.push_back(point(0, 0));
            toThisVector.push_back(point(1, 0));
            toThisVector.push_back(point(1, 1));
            toThisVector.push_back(point(1, 2));
            toThisVector.push_back(point(1, 3));
            toThisVector.push_back(point(1, 4));
            toThisVector.push_back(point(2, 0));
            sizeChar = 3;
            break;
        }
        case 'u':
        case 'U':
        {
            toThisVector.push_back(point(0, 0));
            toThisVector.push_back(point(0, 1));
            toThisVector.push_back(point(0, 2));
            toThisVector.push_back(point(0, 3));
            toThisVector.push_back(point(0, 4));
            toThisVector.push_back(point(1, 4));
            toThisVector.push_back(point(2, 0));
            toThisVector.push_back(point(2, 1));
            toThisVector.push_back(point(2, 2));
            toThisVector.push_back(point(2, 3));
            toThisVector.push_back(point(2, 4));
            sizeChar = 3;
            break;
        }
        case 'v':
        case 'V':
        {
            toThisVector.push_back(point(0, 0));
            toThisVector.push_back(point(0, 1));
            toThisVector.push_back(point(0, 2));
            toThisVector.push_back(point(0, 3));
            toThisVector.push_back(point(1, 4));
            toThisVector.push_back(point(2, 0));
            toThisVector.push_back(point(2, 1));
            toThisVector.push_back(point(2, 2));
            toThisVector.push_back(point(2, 3));
            sizeChar = 3;
            break;
        }
        case 'w':
        case 'W':
        {
            toThisVector.push_back(point(0, 0));
            toThisVector.push_back(point(0, 1));
            toThisVector.push_back(point(0, 2));
            toThisVector.push_back(point(0, 3));
            toThisVector.push_back(point(1, 3));
            toThisVector.push_back(point(1, 4));
            toThisVector.push_back(point(2, 3));
            toThisVector.push_back(point(2, 4));
            toThisVector.push_back(point(3, 0));
            toThisVector.push_back(point(3, 1));
            toThisVector.push_back(point(3, 2));
            toThisVector.push_back(point(3, 3));
            sizeChar = 4;
            break;
        }
        case 'x':
        case 'X':
        {
            toThisVector.push_back(point(0, 0));
            toThisVector.push_back(point(0, 1));
            toThisVector.push_back(point(0, 3));
            toThisVector.push_back(point(0, 4));
            toThisVector.push_back(point(1, 2));
            toThisVector.push_back(point(2, 0));
            toThisVector.push_back(point(2, 1));
            toThisVector.push_back(point(2, 3));
            toThisVector.push_back(point(2, 4));
            sizeChar = 3;
            break;
        }
        case 'y':
        case 'Y':
        {
            toThisVector.push_back(point(0, 0));
            toThisVector.push_back(point(0, 1));
            toThisVector.push_back(point(0, 2));
            toThisVector.push_back(point(1, 2));
            toThisVector.push_back(point(1, 3));
            toThisVector.push_back(point(1, 4));
            toThisVector.push_back(point(2, 0));
            toThisVector.push_back(point(2, 1));
            toThisVector.push_back(point(2, 2));
            sizeChar = 3;
            break;
        }
        case 'z':
        case 'Z':
        {
            toThisVector.push_back(point(0, 0));
            toThisVector.push_back(point(0, 3));
            toThisVector.push_back(point(0, 4));
            toThisVector.push_back(point(1, 0));
            toThisVector.push_back(point(1, 2));
            toThisVector.push_back(point(1, 4));
            toThisVector.push_back(point(2, 0));
            toThisVector.push_back(point(2, 1));
            toThisVector.push_back(point(2, 4));
            sizeChar = 3;
            break;
        }
        case '\'':
        {
            toThisVector.push_back(point(0, 0));
            toThisVector.push_back(point(0, 1));
            sizeChar = 1;
            break;
        }
        case '!':
        {
            toThisVector.push_back(point(0, 0));
            toThisVector.push_back(point(0, 1));
            toThisVector.push_back(point(0, 2));
            toThisVector.push_back(point(0, 4));
            sizeChar = 1;
            break;
        }
        case '.':
        {
            toThisVector.push_back(point(0, 4));
            sizeChar = 1;
            break;
        }
        case ',':
        {
            toThisVector.push_back(point(0, 4));
            toThisVector.push_back(point(0, 5));
            sizeChar = 1;
            break;
        }
        case ' ':
        {
            sizeChar = 1;
            break;
        }

    }

    return sizeChar;
}
