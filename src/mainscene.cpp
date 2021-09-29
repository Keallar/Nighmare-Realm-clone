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
    fontMain.loadFromFile("../data/fonts/font.ttf");
    textWin.setFont(fontMain);
    textWin.setString(" You \n win!\nPress\nReset\n   to\nrestart\n game");
    textWin.setCharacterSize(65);
    textWin.setFillColor(sf::Color::Black);
    textWin.setPosition({50, 240});
    textControll.setFont(fontMain);
    textControll.setString("Controlling:\n A - move left\n D - move right\n W - move up\n S - move down\n Cursor and click-\n choose a chip");
    textControll.setCharacterSize(30);
    textControll.setFillColor(sf::Color::Black);
    textControll.setPosition({1000, 400});
    oFactory = objectsFactory::getInstance();
    gController = new gameController{};
    isWon = false;
    isRules = false;
    createField();
    createUnits();
    gController->addUnits(unitsYellow);
    gController->addUnits(unitsRed);
    gController->addUnits(unitsBlue);
    createExUnits();
    rulObj = new rules(renWindow);
    rulObj->init();
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
    if (!isWon) {
        checkWinPos();
    }
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
    if (isWon) {
        renWindow->draw(textWin);
    }
    if (isRules) {
        rulObj->render();
    }
    renWindow->draw(textControll);
}

void mainScene::reset() {
    unitsYellow.clear();
    unitsRed.clear();
    unitsBlue.clear();
    unitsEx.clear();
    gController->reset();
    isWon = false;
    createUnits();
    //createUnitsGarb();
    createExUnits();
    //createExUnitsGarb();
    gController->addUnits(unitsYellow);
    gController->addUnits(unitsRed);
    gController->addUnits(unitsBlue);
}

void mainScene::createGui() {
    ImGui::Begin("Interface");
    ImGui::SetWindowPos({1050, 50});
    ImGui::SetWindowSize({180, 180});
    if (ImGui::Button("Reset")) {
        reset();
    }
    if (ImGui::Button("Rules")){
        if (isRules) {
            isRules = false;
        } else {
            isRules = true;
        }
    }
    if (ImGui::Button("Close")) {
        renWindow->close();
    }
    ImGui::End();
}

void mainScene::createField() {
    for (int i = 0; i < COUNT_OF_CELLS; ++i) {
        for (int j = 0; j < COUNT_OF_CELLS; ++j) {
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
    int checkedYell {0};
    bool redInOneLine {false};
    int checkedRed {0};
    bool blueInOneLine {false};
    int checkedBlue {0};
    for (auto exUnit : unitsEx) {
        auto idEx = exUnit->getID();
        int posXEx = exUnit->getX();
        int widthEx = exUnit->getWidth();
        if (idEx == "unit_yellow_ex") {
            idEx.pop_back();
            idEx.pop_back();
            idEx.pop_back();
            for (auto yellUnit : unitsYellow) {
                auto idYellUn = yellUnit->getID();
                idYellUn.pop_back();
                idYellUn.pop_back();
                idYellUn.pop_back();
                if (idYellUn == idEx) {
                    int posX = yellUnit->getX();
                    int width = 127;
                    if (posX >= posXEx && posX + width <= posXEx + widthEx) {
                        checkedYell++;
                    }
                }
            }
            if (checkedYell != 5) {
                return;
            }
            yellInOneLine = true;
        }
        if (idEx == "unit_red_ex") {
            idEx.pop_back();
            idEx.pop_back();
            idEx.pop_back();
            for (auto redUnit : unitsRed) {
                auto idRedUn = redUnit->getID();
                idRedUn.pop_back();
                idRedUn.pop_back();
                idRedUn.pop_back();
                if (idRedUn == idEx) {
                    int posX = redUnit->getX();
                    int width = 127;
                    if (posX >= posXEx && posX + width <= posXEx + widthEx) {
                        checkedRed++;
                    }
                }
            }
            if (checkedRed != 5) {
                return;
            }
            redInOneLine = true;
        }
        if (idEx == "unit_blue_ex") {
            idEx.pop_back();
            idEx.pop_back();
            idEx.pop_back();
            for (auto blueUnit : unitsBlue) {
                auto idBlueUn = blueUnit->getID();
                idBlueUn.pop_back();
                idBlueUn.pop_back();
                idBlueUn.pop_back();
                if (idBlueUn == idEx) {
                    int posX = blueUnit->getX();
                    int width = 127;
                    if (posX >= posXEx && posX + width <= posXEx + widthEx) {
                        checkedBlue++;
                    }
                }
            }
            if (checkedBlue != 5) {
                return;
            }
            blueInOneLine = true;
        }
    }
    if (yellInOneLine == true && redInOneLine == true && blueInOneLine == true) {
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

