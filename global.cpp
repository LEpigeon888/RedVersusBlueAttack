#include "global.hpp"

double global::timeFrame = 0;
sf::Color global::grey = sf::Color(200, 200, 200);
sf::RenderWindow global::window;
gameStateStackClass global::gameStateStack;
sf::Font global::font;
sf::Vector2u global::sizeWindow(960, 720);
bool global::isFullScreen = false;
bool global::isFourThirds = true;
int global::sizeChar = 30;
typeSound global::soundType = ALL;
soundManagerClass* global::soundManager;
bool global::run = true;
std::string global::windowName = "Red Versus Blue: Attack v1.8";
