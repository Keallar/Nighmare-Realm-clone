#pragma once
#include "SFML/Graphics.hpp"
#include <string>

class rules {
public:
    rules(sf::RenderWindow* window);
    void init();
    void render();
private:
    sf::RenderWindow* renWin;
    sf::RectangleShape* rectList;
    sf::Font fontText;
    sf::Text textRul;
    std::string strText;
};

