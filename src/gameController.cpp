#pragma once
#include "gameController.h"

gameController::~gameController() {
    allUnits.clear();
    blockedCells.clear();
}

void init() {

}

void gameController::notify(GameObject *object, std::string event) {

}

bool gameController::collWithBlockedCell(const unit* checkedUnit) {
    bool isCollided;
    auto xUnit = checkedUnit->getX() - 2;
    auto yUnit = checkedUnit->getY() - 2;
    auto wUnit = checkedUnit->getWidth() - 6;
    auto hUnit = checkedUnit->getHeight() - 6;
    for (size_t i = 0; i < blockedCells.size(); ++i) {
        auto xBlCell = blockedCells.at(i).first.x + 1;
        auto yBlCell = blockedCells.at(i).first.y + 1;
        auto wBlCell = blockedCells.at(i).second.x - 2;
        auto hBlCell = blockedCells.at(i).second.y - 2;
        isCollided = collision(xUnit, yUnit, wUnit, hUnit, xBlCell, yBlCell, wBlCell, hBlCell);
        if (isCollided) {
            //std::cout << i << std::endl;
            return true;
        }
    }
    return false;
}

bool gameController::collWithOtherUnit(const unit* checkedUnit) {
    bool isCollided;
    auto xUnit = checkedUnit->getX();
    auto yUnit = checkedUnit->getY();
    auto wUnit = checkedUnit->getWidth();
    auto hUnit = checkedUnit->getHeight();
    for (size_t i = 0; i < allUnits.size(); ++i) {
        auto checkUnitID = checkedUnit->getID();
        auto otherUnitID = allUnits.at(i)->getID();
        if (checkUnitID != otherUnitID) {
            auto xOtherUnit = allUnits.at(i)->getX();
            auto yOtherUnit = allUnits.at(i)->getY();
            auto wOtherUnit = allUnits.at(i)->getWidth();
            auto hOtherUnit = allUnits.at(i)->getHeight();
            isCollided = collision(xUnit, yUnit, wUnit, hUnit, xOtherUnit, yOtherUnit, wOtherUnit, hOtherUnit);
            if (isCollided) {
                std::cout << i << std::endl;
                return true;
            }
        }
    }
    return false;
}

void gameController::addUnits(std::vector<unit*> gotUnits) {
    allUnits.reserve(allUnits.size() + gotUnits.size());
    allUnits.insert(allUnits.end(), gotUnits.begin(), gotUnits.end());
}

void gameController::addBlockedCells(sf::Vector2f vecCooords, sf::Vector2f vecSize) {
    auto bCell = std::make_pair(vecCooords, vecSize);
    blockedCells.push_back(bCell);
}

bool gameController::collision(int aX, int aY, int aW, int aH, int bX, int bY, int bW, int bH) {
    int x1Min = aX;
    int y1Min = aY;
    int x1Max = aX + aW;
    int y1Max = aY + aH;

    int x2Min = bX;
    int y2Min = bY;
    int x2Max = bX + bW;
    int y2Max = bY + bH;

    // Collision tests
    if (x1Max < x2Min || x1Min > x2Max) {
        return false;
    }
    if (y1Max < y2Min || y1Min > y2Max) {
        return false;
    }
    return true;
}
