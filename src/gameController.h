#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <map>
#include <string>
#include <memory>
#include "mainController.h"
#include "objectsFactory.h"

class gameObject;

class gameController : public MainController {
public:
    gameController() = default;
    ~gameController();
    void init();
    void notify(GameObject* object, std::string event) override;
    bool collWithBlockedCell(const unit* checkedUnit);
    bool collWithOtherUnit(const unit* checkedUnit);
    bool collision(int aX, int aY, int aW, int aH, int bX, int bY, int bW, int bH);
    void addUnits(std::vector<unit*> gotUnits);
    void addBlockedCells(sf::Vector2f vecCooords, sf::Vector2f vecSize);
private:
    std::vector<unit*> allUnits;
    std::vector<std::pair<sf::Vector2f, sf::Vector2f>> blockedCells;
};


