#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <map>
#include "gameController.h"
#include "objectsFactory.h"
#include "unit.h"

class mainScene {
public:
    mainScene(sf::RenderWindow* window);
    ~mainScene();
    void init();
    void update(sf::Time deltaTime);
    void render();
    void createField();
    void createUnits();
    void createExUnits();
    void handleEvents(sf::Mouse::Button button);
private:
    const int COUNT_OF_CELLS = 5;
    const int COUNT_OF_UNITS = 5;

    sf::RenderWindow* renWindow;
    std::map<std::string, sf::RectangleShape*> cells;
    std::vector<unit*> unitsYellow;
    std::vector<unit*> unitsRed;
    std::vector<unit*> unitsBlue;
    std::vector<unit*> unitsEx;
    gameController* gController;
    objectsFactory* oFactory;
};

