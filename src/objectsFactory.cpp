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
    yellUnit->setColor(sf::Color::Yellow);
    yellUnit->setID("yellow_");
    yellUnit->setRadius(63);
    yellUnit->setAnchor(0.5f, 0.5f);
    yellUnit->getCircle().setOutlineColor(sf::Color::Black);
    yellUnit->getCircle().setOutlineThickness(1.0f);
    return yellUnit;
}

unit *objectsFactory::createRedUnit() {
    auto redUnit = new unit{};
    redUnit->setColor(sf::Color::Red);
    redUnit->setID("red_");
    redUnit->setRadius(63);
    redUnit->setAnchor(0.5f, 0.5f);
    redUnit->getCircle().setOutlineColor(sf::Color::Black);
    redUnit->getCircle().setOutlineThickness(1.0f);
    return redUnit;
}

unit *objectsFactory::createBlueUnit() {
    auto blueUnit = new unit{};
    blueUnit->setColor(sf::Color::Blue);
    blueUnit->setID("blue_");
    blueUnit->setRadius(63);
    blueUnit->setAnchor(0.5f, 0.5f);
    blueUnit->getCircle().setOutlineColor(sf::Color::Black);
    blueUnit->getCircle().setOutlineThickness(1.0f);
    return blueUnit;
}

