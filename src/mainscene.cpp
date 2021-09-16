#pragma once
#include "mainscene.h"
#include <iostream>
#include <random>
#include <ctime>
#include <algorithm>

const int COUNT_OF_CELLS = 5;
const int COUNT_OF_UNITS = 5;

mainScene::mainScene(sf::RenderWindow* window)
    : renWindow(window) {
}

mainScene::~mainScene() {
    cells.clear();
    unitsYellow.clear();
    unitsRed.clear();
    unitsBlue.clear();
    unitsEx.clear();
    delete oFactory;
    delete gController;
}

void mainScene::init() {
    oFactory = objectsFactory::getInstance();
    gController = new gameController{};
    createField();
    createUnits();
    createExUnits();
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
    for (auto exUnit : unitsEx) {
        exUnit->render();
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
            if (i == 1 && j == 0) {
                tempCell->setFillColor(sf::Color(105, 105, 105));
            }
            if (i == 3 && j == 0) {
                tempCell->setFillColor(sf::Color(105, 105, 105));
            }
            if (i == 1 && j == 2) {
                tempCell->setFillColor(sf::Color(105, 105, 105));
            }
            if (i == 3 && j == 2) {
                tempCell->setFillColor(sf::Color(105, 105, 105));
            }
            if (i == 1 && j == 4) {
                tempCell->setFillColor(sf::Color(105, 105, 105));
            }
            if (i == 3 && j == 4) {
                tempCell->setFillColor(sf::Color(105, 105, 105));
            }
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
        if (k == 1 || k == 3) {
            tempCell->setFillColor(sf::Color(105, 105, 105));
        }
        tempCell->setOutlineColor(sf::Color::Black);
        tempCell->setOutlineThickness(2.0f);
        cells.insert(std::make_pair("cellEx " + std::to_string(k), tempCell));
    }
}

void mainScene::createUnits() {
    bool yellIsFull {false};
    bool redIsFull {false};
    bool blueIsFull {false};
    bool isCreated {false};
    bool allIsCreated {false};
    srand(time(0));
    int numUnit = 0;
    int i = 0;
    int j = 0;
    while (!allIsCreated)  {
        numUnit = std::rand() % 3;
        if (numUnit == 0) {
            if (unitsYellow.size() == 5) {
                yellIsFull = true;
            }
            if (!yellIsFull) {
                auto yellUnit = oFactory->createYellowUnit();
                yellUnit->setWindow(renWindow);
                auto posX = 300.f + 130.f * i * 2 + 2.f;
                auto posY = 200.f + 130.f * j + 2.f;
                yellUnit->setStartPos(posX, posY);
                unitsYellow.push_back(yellUnit);
                isCreated = true;
            }
        }
        if (numUnit == 1) {
            if (unitsRed.size() == 5) {
                redIsFull = true;
            }
            if (!redIsFull) {
                auto redUnit = oFactory->createRedUnit();
                redUnit->setWindow(renWindow);
                auto posX = 300.f + 130.f * i * 2 + 2.f;
                auto posY = 200.f + 130.f * j + 2.f;
                redUnit->setStartPos(posX, posY);
                unitsRed.push_back(redUnit);
                isCreated = true;
            }
        }
        if (numUnit == 2) {
            if (unitsBlue.size() == 5) {
                blueIsFull = true;
            }
            if (!blueIsFull) {
                auto blueUnit = oFactory->createBlueUnit();
                blueUnit->setWindow(renWindow);
                auto posX = 300.f + 130.f * i * 2 + 2.f;
                auto posY = 200.f + 130.f * j + 2.f;
                blueUnit->setStartPos(posX, posY);
                unitsBlue.push_back(blueUnit);
                isCreated = true;
            }
        }
        if (isCreated){
            j++;
            if (j == 5) {
                i++;
                j = 0;
            }
            isCreated = false;
        }
        if (yellIsFull == true && redIsFull == true && blueIsFull == true) {
            allIsCreated = true;
        }
    }
}

void mainScene::createExUnits() {
    std::vector<int> numEx {0, 1, 2};
    std::random_shuffle(numEx.begin(), numEx.end());
    for (int i = 0; i < 3; ++i) {
        unit* tempUnit;
        if (i == 0) {
            tempUnit = oFactory->createYellowUnit();
        }
        if (i == 1) {
            tempUnit = oFactory->createRedUnit();
        }
        if (i == 2) {
            tempUnit = oFactory->createBlueUnit();
        }
        tempUnit->setWindow(renWindow);
        auto posX = 300.f + 130.f * numEx.at(i) * 2.f + 2.f;
        auto posY = 30.f;
        tempUnit->setStartPos(posX, posY);
        unitsBlue.push_back(tempUnit);
    }
}

void mainScene::handleEvents(sf::Mouse::Button button, bool isPressed){
    isMouseOverObject();
}

void mainScene::isMouseOverObject() {
    auto mousePos = sf::Mouse::getPosition(*renWindow);
    std::cout << mousePos.x << " " << mousePos.y << std::endl;
}
