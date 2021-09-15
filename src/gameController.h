#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <map>
#include <string>
#include <memory>
#include "mainController.h"
#include "objectsFactory.h"

class gameObject;

class gameController : public MainController {
public:
    gameController() = default;
    void init();
    void notify(GameObject* object, std::string event) override;
    void collision();
private:
    std::map<std::string, GameObject*> objects;
    objectsFactory* oFactory;
};


