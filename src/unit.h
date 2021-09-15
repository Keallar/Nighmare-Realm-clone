#pragma once
#include "gameObject.h"

class unit : public gameObject {
public:
    unit() = default;
    void init() override;
    void update(sf::Time time) override;
    void reset();
    void moving(sf::Time time);
private:
    const int WIDTH {800};
    const int HEIGHT {600};
    bool isPressed;
};

