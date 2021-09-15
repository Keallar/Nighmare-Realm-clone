#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <map>
#include "gameController.h"
#include "unit.h"

class mainScene {
public:
    mainScene(sf::RenderWindow* window);
    ~mainScene();
    void init();
    void update(sf::Time deltaTime);
    void render();
    void createField();
    void handleEvents(sf::Mouse::Button button, bool isPressed);
private:
    sf::RenderWindow* renWindow;
    std::map<std::string, sf::RectangleShape*> cells;
    std::map<std::string, unit*> units;
    gameController* gController;
};

