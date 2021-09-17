#include "objectsFactory.h"

objectsFactory* objectsFactory::instance = nullptr;

objectsFactory *objectsFactory::getInstance() {
    if (instance == nullptr) {
        instance = new objectsFactory{};
    }
    return instance;
}

unit *objectsFactory::createYellowUnit() {
    auto yellUnit = new unit{};
    yellUnit->init();
    yellUnit->setColor(sf::Color::Yellow);
    yellUnit->setID("yellow_");
    yellUnit->setRadius(63);
    yellUnit->setAnchor(0.5f, 0.5f);
    auto tempCirc = yellUnit->getCircle();
    tempCirc.setOutlineColor(sf::Color::Black);
    tempCirc.setOutlineThickness(1.0f);
    yellUnit->setCircle(tempCirc);
    return yellUnit;
}

unit *objectsFactory::createRedUnit() {
    auto redUnit = new unit{};
    redUnit->init();
    redUnit->setColor(sf::Color::Red);
    redUnit->setID("red_");
    redUnit->setRadius(63);
    redUnit->setAnchor(0.5f, 0.5f);
    auto tempCirc = redUnit->getCircle();
    tempCirc.setOutlineColor(sf::Color::Black);
    tempCirc.setOutlineThickness(1.0f);
    redUnit->setCircle(tempCirc);
    return redUnit;
}

unit *objectsFactory::createBlueUnit() {
    auto blueUnit = new unit{};
    blueUnit->init();
    blueUnit->setColor(sf::Color::Blue);
    blueUnit->setID("blue_");
    blueUnit->setRadius(63);
    blueUnit->setAnchor(0.5f, 0.5f);
    auto tempCirc = blueUnit->getCircle();
    tempCirc.setOutlineColor(sf::Color::Black);
    tempCirc.setOutlineThickness(1.0f);
    blueUnit->setCircle(tempCirc);
    return blueUnit;
}

