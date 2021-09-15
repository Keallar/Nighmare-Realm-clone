#pragma once
#include "mainscene.h"
#include <iostream>
#include <random>

const int COUNT_OF_CELLS = 5;
const int COUNT_OF_UNITS = 5;

mainScene::mainScene(sf::RenderWindow* window)
    : renWindow(window) {
    oFactory = objectsFactory::getInstance();
}

mainScene::~mainScene() {
    cells.clear();
    unitsYellow.clear();
    unitsRed.clear();
    unitsBlue.clear();
}

void mainScene::init() {
    createField();
    createUnits();
}

void mainScene::update(sf::Time deltaTime) {

}

void mainScene::render() {
    for (auto cell : cells) {
        renWindow->draw(*cell.second);
    }
    for (auto yUnit : unitsYellow) {
        yUnit->render();
    }
    for (auto rUnit : unitsRed) {
        rUnit->render();
    }
    for (auto bUnit : unitsBlue) {
        bUnit->render();
    }
}

void mainScene::createField() {
    for (size_t i = 0; i < 5; ++i) {
        for (size_t j = 0; j < 5; ++j) {
            auto tempCell = new sf::RectangleShape{};
            sf::Vector2f cellSize {130.0f, 130.0f};
            sf::Vector2f cellPos {300.0f + (130.0f * i), 200.0f + (130.f * j)};
            tempCell->setSize(cellSize);
            tempCell->setPosition(cellPos);
            tempCell->setFillColor(sf::Color::White);
            tempCell->setOutlineColor(sf::Color::Black);
            tempCell->setOutlineThickness(2.0f);
            cells.insert(std::make_pair("cell " + std::to_string(i) + std::to_string(j), tempCell));

        }
    }

    for (size_t k = 0; k < 5; ++k) {
        auto tempCell = new sf::RectangleShape{};
        sf::Vector2f cellSize {130.0f, 130.0f};
        sf::Vector2f cellPos {300.0f + (130.0f * k), 30.0f};
        tempCell->setSize(cellSize);
        tempCell->setPosition(cellPos);
        tempCell->setFillColor(sf::Color::White);
        tempCell->setOutlineColor(sf::Color::Black);
        tempCell->setOutlineThickness(2.0f);
        cells.insert(std::make_pair("cellEx " + std::to_string(k), tempCell));
    }
}

void mainScene::createUnits() {
    bool yellIsFull {false};
    bool redIsFull {false};
    bool blueIsFull {false};
    for (size_t i = 0; i < 5; ++i) {
        for (size_t j = 0; j < 5; ++j) {
            srand(time(0));
            int numUnit = std::rand() % 3;
            if (numUnit == 0 && yellIsFull == false) {
                if (unitsYellow.size() == 5) {
                    yellIsFull = true;
                    break;
                } else {
                    auto yellUnit = oFactory->createYellowUnit();
                    yellUnit->setWindow(renWindow);
                    auto xPos = 300 + 130 * i + 2;
                    auto yPos = 200 + 130 * j + 2;
                    yellUnit->setStartPos(xPos, yPos);
                    unitsYellow.push_back(yellUnit);
                }
            }
            if (numUnit == 1 && redIsFull == false) {
                if (unitsRed.size() == 5) {
                    redIsFull = true;
                    break;
                } else {
                    auto redUnit = oFactory->createRedUnit();
                    redUnit->setWindow(renWindow);
                    auto xPos = 300 + 130 * i + 2;
                    auto yPos = 200 + 130 * j + 2;
                    redUnit->setStartPos(xPos, yPos);
                    unitsRed.push_back(redUnit);
                }
            }
            if (numUnit == 2 && blueIsFull == false) {
                if (unitsBlue.size() == 5) {
                    blueIsFull = true;
                    break;
                } else {
                    auto blueUnit = oFactory->createBlueUnit();
                    blueUnit->setWindow(renWindow);
                    auto xPos = 300 + 130 * i + 2;
                    auto yPos = 200 + 130 * j + 2;
                    blueUnit->setStartPos(xPos, yPos);
                    unitsBlue.push_back(blueUnit);
                }
            }
        }
    }
}

void mainScene::handleEvents(sf::Mouse::Button button, bool isPressed){

}
