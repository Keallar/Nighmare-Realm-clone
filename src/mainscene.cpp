#pragma once
#include "mainscene.h"
#include <iostream>
#include <random>
#include <ctime>
#include <algorithm>
#include "imgui-SFML.h"
#include "imgui.h"

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
    fontMain.loadFromFile("../data/Fonts/font.ttf");
    textWin.setFont(fontMain);
    textWin.setString("You win");
    textWin.setCharacterSize(64);
    textWin.setFillColor(sf::Color::Green);
    textWin.setPosition({100, 400});
    oFactory = objectsFactory::getInstance();
    gController = new gameController{};
    isWon = false;
    createField();
    createUnits();
    gController->addUnits(unitsYellow);
    gController->addUnits(unitsRed);
    gController->addUnits(unitsBlue);
    createExUnits();
}

void mainScene::update(sf::Time deltaTime) {
    if (isWon) {
        return;
    }
    for (auto yUnit : unitsYellow) {
        yUnit->update(deltaTime);
    }
    for (auto rUnit : unitsRed) {
        rUnit->update(deltaTime);
    }
    for (auto bUnit : unitsBlue) {
        bUnit->update(deltaTime);
    }
    checkWinPos();
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
    renWindow->draw(textWin);
}

void mainScene::reset() {
    unitsYellow.clear();
    unitsRed.clear();
    unitsBlue.clear();
    unitsEx.clear();
    gController->reset();
    isWon = false;
    createUnits();
    createExUnits();
    gController->addUnits(unitsYellow);
    gController->addUnits(unitsRed);
    gController->addUnits(unitsBlue);
}

void mainScene::createGui() {
    ImGui::Begin("Interface");
    ImGui::SetWindowPos({1050, 50});
    ImGui::SetWindowSize({180, 180});
    if (ImGui::Button("Reset")) {
        //reset();
    }
    if (ImGui::Button("Rules")){

    }
    if (ImGui::Button("Close")) {

    }
    ImGui::End();
}

void mainScene::createField() {
    for (size_t i = 0; i < COUNT_OF_CELLS; ++i) {
        for (size_t j = 0; j < COUNT_OF_CELLS; ++j) {
            auto tempCell = new sf::RectangleShape{};
            sf::Vector2f cellSize {130.0f, 130.0f};
            sf::Vector2f cellPos {300.0f + (130.0f * i), 200.0f + (130.f * j)};
            tempCell->setSize(cellSize);
            tempCell->setPosition(cellPos);
            tempCell->setFillColor(sf::Color::White);
            if (i == 1 && j == 0) {
                tempCell->setFillColor(sf::Color(105, 105, 105));
                gController->addBlockedCells(cellPos, cellSize);
            }
            if (i == 3 && j == 0) {
                tempCell->setFillColor(sf::Color(105, 105, 105));
                gController->addBlockedCells(cellPos, cellSize);
            }
            if (i == 1 && j == 2) {
                tempCell->setFillColor(sf::Color(105, 105, 105));
                gController->addBlockedCells(cellPos, cellSize);
            }
            if (i == 3 && j == 2) {
                tempCell->setFillColor(sf::Color(105, 105, 105));
                gController->addBlockedCells(cellPos, cellSize);
            }
            if (i == 1 && j == 4) {
                tempCell->setFillColor(sf::Color(105, 105, 105));
                gController->addBlockedCells(cellPos, cellSize);
            }
            if (i == 3 && j == 4) {
                tempCell->setFillColor(sf::Color(105, 105, 105));
                gController->addBlockedCells(cellPos, cellSize);
            }
            tempCell->setOutlineColor(sf::Color::Black);
            tempCell->setOutlineThickness(2.0f);
            cells.insert(std::make_pair("cell " + std::to_string(i) + std::to_string(j), tempCell));

        }
    }

    for (size_t k = 0; k < COUNT_OF_CELLS; ++k) {
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
        cells.insert(std::make_pair("cellEx " + std::to_string(k), tempCell));    }
}

void mainScene::createUnits() {
    bool yellIsFull {false};
    bool redIsFull {false};
    bool blueIsFull {false};
    bool isCreated {false};
    bool allIsCreated {false};
    srand(static_cast<unsigned int>(time(nullptr)));
    int numUnit {0};
    int i {0};
    int j {0};
    while (!allIsCreated)  {
        numUnit = std::rand() % 3;
        if (numUnit == 0) {
            if (unitsYellow.size() == COUNT_OF_UNITS) {
                yellIsFull = true;
            }
            if (!yellIsFull) {
                auto yellUnit = oFactory->createYellowUnit();
                yellUnit->setWindow(renWindow);
                yellUnit->setIsMoving(true);
                auto posX = 300 + 130 * i * 2 + 2;
                auto posY = 200 + 130 * j + 2;
                yellUnit->setStartPos(posX, posY);
                yellUnit->setID(std::to_string(i) + std::to_string(j));
                yellUnit->setController(gController);
                unitsYellow.push_back(yellUnit);
                isCreated = true;
            }
        }
        if (numUnit == 1) {
            if (unitsRed.size() == COUNT_OF_UNITS) {
                redIsFull = true;
            }
            if (!redIsFull) {
                auto redUnit = oFactory->createRedUnit();
                redUnit->setWindow(renWindow);
                redUnit->setIsMoving(true);
                auto posX = 300 + 130 * i * 2 + 2;
                auto posY = 200 + 130 * j + 2;
                redUnit->setStartPos(posX, posY);
                redUnit->setID(std::to_string(i) + std::to_string(j));
                redUnit->setController(gController);
                unitsRed.push_back(redUnit);
                isCreated = true;
            }
        }
        if (numUnit == 2) {
            if (unitsBlue.size() == COUNT_OF_UNITS) {
                blueIsFull = true;
            }
            if (!blueIsFull) {
                auto blueUnit = oFactory->createBlueUnit();
                blueUnit->setWindow(renWindow);
                blueUnit->setIsMoving(true);
                auto posX = 300 + 130 * i * 2 + 2;
                auto posY = 200 + 130 * j + 2;
                blueUnit->setStartPos(posX, posY);
                blueUnit->setID(std::to_string(i) + std::to_string(j));
                blueUnit->setController(gController);
                unitsBlue.push_back(blueUnit);
                isCreated = true;
            }
        }
        if (isCreated){
            j++;
            if (j == COUNT_OF_UNITS) {
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
        tempUnit->setIsMoving(false);
        auto posX = 300 + 130 * numEx.at(i) * 2 + 2;
        auto posY = 30;
        tempUnit->setStartPos(posX, posY);
        tempUnit->setID("ex");
        unitsEx.push_back(tempUnit);
    }
}

void mainScene::checkWinPos() {
    bool yellInOneLine {false};
    bool redInOneLine {false};
    bool blueInOneLine {false};
    for (auto exUnit : unitsEx) {
        auto idEx = exUnit->getID();
        auto posXEx = exUnit->getX();
        auto widthEx = exUnit->getWidth();
        if (idEx == "unit_yellow_ex") {
            for (auto yellUnit : unitsYellow) {
                auto posX = yellUnit->getX();
                if (posX < posXEx && posX > posXEx + widthEx) {
                    return;
                }
            }
            yellInOneLine = true;
        }
        if (idEx == "unit_red_ex") {
            for (auto redUnit : unitsRed) {
                auto posX = redUnit->getX();
                if (posX < posXEx && posX > posXEx + widthEx) {
                    return;
                }
            }
            redInOneLine = true;
        }
        if (idEx == "unit_blue_ex") {
            for (auto blueUnit : unitsBlue) {
                auto posX = blueUnit->getX();
                if (posX < posXEx && posX > posXEx + widthEx) {
                    return;
                }
            }
            blueInOneLine = true;
        }
    }
    if (yellInOneLine || redInOneLine || blueInOneLine) {
        isWon = true;
    }
}

void mainScene::handleEvents(sf::Mouse::Button button){
    for (auto yellUnit : unitsYellow) {
        yellUnit->checkMouse(button);
    }
    for (auto redUnit : unitsRed) {
        redUnit->checkMouse(button);
    }
    for (auto blueUnit : unitsBlue) {
        blueUnit->checkMouse(button);
    }
}

