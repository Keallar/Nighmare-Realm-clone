#pragma once
#include "mainscene.h"
#include <iostream>

mainScene::mainScene(sf::RenderWindow* window)
    : renWindow(window) {

}

mainScene::~mainScene() {
    cells.clear();
}

void mainScene::init() {
    for (size_t i = 0; i < 5; ++i) {
        for (size_t j = 0; j < 5; ++j) {
            auto tempCell = new sf::RectangleShape{};
            sf::Vector2f cellSize {130.0f, 130.0f};
            sf::Vector2f cellPos {300.0f + (130.0f * i), 150.0f + (130.f * j)};
            tempCell->setSize(cellSize);
            tempCell->setPosition(cellPos);
            tempCell->setFillColor(sf::Color::White);
            tempCell->setOutlineColor(sf::Color::Black);
            tempCell->setOutlineThickness(2.0f);
            cells.insert(std::make_pair(std::to_string(i) + std::to_string(j), tempCell));

        }
    }
}

void mainScene::update(sf::Time deltaTime) {

}

void mainScene::render() {
    for (auto cell : cells) {
        renWindow->draw(*cell.second);
    }
}

void mainScene::createField() {

}

void mainScene::handleEvents(sf::Mouse::Button button, bool isPressed){


}
