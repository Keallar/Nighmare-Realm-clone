#pragma once
#include "gameObject.h"

class unit : public gameObject {
public:
    unit() = default;
    void init() override;
    void update(sf::Time time) override;
    void edgeCollision();
    void reset();
    void moving(sf::Time time);
private:
    const int WIDTH {1280};
    const int HEIGHT {960};
    bool isPressed;
};

