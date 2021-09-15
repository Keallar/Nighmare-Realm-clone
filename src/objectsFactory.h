#pragma once
#include <iostream>
#include "unit.h"

class GameObject;

class objectsFactory
{
public:
    objectsFactory(const objectsFactory&) = delete;
    void operator = (const objectsFactory&) = delete;
    static objectsFactory* getInstance();
    static gameObject* createUnit();
protected:
    objectsFactory() = default;
    static objectsFactory* instance;
};

