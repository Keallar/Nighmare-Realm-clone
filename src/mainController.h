#pragma once
#include <string>

class GameObject;

class MainController {
public:
    virtual void notify(GameObject* object, std::string event) = 0;
};

