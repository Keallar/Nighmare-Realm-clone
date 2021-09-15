#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "mainscene.h"

class loop {
public:
    loop();
    ~loop();
    void run();
    void update(sf::Time deltaTime);
    void render();
    void processEvents();
    void handlePlayerInput(sf::Mouse::Button, bool isPressed);
private:
    static const sf::Time TimePerFrame;
    sf::RenderWindow winMain;
    mainScene scene;
};

