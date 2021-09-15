#include "objectsFactory.h"

objectsFactory* objectsFactory::instance = nullptr;

objectsFactory *objectsFactory::getInstance() {
    if (instance == nullptr) {
        instance = new objectsFactory{};
    }
    return instance;
}

gameObject *objectsFactory::createUnit() {
    return new unit{};
}

