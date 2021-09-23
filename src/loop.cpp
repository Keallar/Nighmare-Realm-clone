#include <iostream>
#include <string>
#include "loop.h"
#include "imgui-SFML.h"

const sf::Time loop::TimePerFrame = sf::seconds(1.f/60.f);

loop::loop()
    : winMain(sf::VideoMode(1280, 960), "WARGAMING_test_exercise"), scene(&winMain){
    winMain.setVerticalSyncEnabled(true);
    scene.init();
}

loop::~loop() {
}

void loop::run() {

    ImGui::SFML::Init(winMain);

    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;

    while(winMain.isOpen()) {
        processEvents();
        timeSinceLastUpdate += clock.restart();
        while (timeSinceLastUpdate > TimePerFrame) {
            timeSinceLastUpdate -= TimePerFrame;
            processEvents();
            update(TimePerFrame);
        }
        ImGui::SFML::Update(winMain, TimePerFrame);
        scene.createGui();
        render();
    }
    ImGui::SFML::Shutdown();
}

void loop::update(sf::Time deltaTime) {
    scene.update(deltaTime);
}

void loop::render() {
    winMain.clear(sf::Color(192, 192, 192));
    scene.render();
    ImGui::SFML::Render(winMain);
    winMain.display();
}

void loop::processEvents() {
    sf::Event event;
    while (winMain.pollEvent(event)) {
        ImGui::SFML::ProcessEvent(event);
        switch (event.type) {
        case sf::Event::Closed:
            winMain.close();
            break;
        case sf::Event::MouseButtonPressed:
            handlePlayerInput(event.mouseButton.button, true);
            break;
        case sf::Event::MouseButtonReleased:
            handlePlayerInput(event.mouseButton.button, false);
            break;
        default:
            break;
        }
    }
}

void loop::handlePlayerInput(sf::Mouse::Button button, bool isPressed) {
    scene.handleEvents(button);
}

