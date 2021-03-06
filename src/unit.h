#pragma once
#include "gameObject.h"

enum class eDirection {
    Nowhere,
    Left,
    Right,
    Up,
    Bottom
};

class unit : public gameObject {
public:
    unit() = default;
    void init() override;
    void update(sf::Time time) override;
    void moving(sf::Time time);
    int getNextPosX();
    int getNextPosY();
    int getPrevPosX();
    int getPrevPosY();
    void checkLeft();
    void checkRight();
    void checkUp();
    void checkBottom();
    void moveToLeft(float motion);
    void moveToRight(float motion);
    void moveToUp(float motion);
    void moveToBottom(float motion);
    void setIsMoving(bool state);
    void checkMouse(sf::Mouse::Button button);
    void chooseUnit();
private:
    const int WIDTH {1280};
    const int HEIGHT {960};
    bool isPressed;
    bool isMoving;
    bool moveOver;
    float speed;
    int nextPosX;
    int prevPosX;
    int prevPosY;
    int nextPosY;
    eDirection dir;
};

