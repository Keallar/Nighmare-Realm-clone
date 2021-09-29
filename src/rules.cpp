#include "rules.h"

rules::rules(sf::RenderWindow* window) :
    renWin(window) {
}

void rules::init() {
    fontText.loadFromFile("../data/fonts/font.ttf");
    rectList = new sf::RectangleShape;
    rectList->setPosition({300, 200});
    rectList->setFillColor(sf::Color::White);
    rectList->setSize({650, 650});
    textRul.setFont(fontText);
    strText = "\t\t\t\t RULES\n\n"
"\tYour goal is to arrange all\n"
"\tthe chips of the same color\n"
"\ton the same line and in\n"
"\taccordance with the example\n"
"\tchips.";
    textRul.setString(strText);
    textRul.setCharacterSize(32);
    textRul.setFillColor(sf::Color::Black);
    textRul.setPosition({300, 300});
}

void rules::render() {
    renWin->draw(*rectList);
    renWin->draw(textRul);
}
