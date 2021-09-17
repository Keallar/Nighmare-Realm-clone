#include "unit.h"
#include <iostream>

void unit::init() {
    setID("unit_");
    setRadius(60.0f);
    //setAnchor(30.f, 30.f);
    state = eState::Start;
    speed = 0.3;
    isPressed = false;
    isMoving = false;
    moveOver = false;
    dir = eDirection::Nowhere;
}

void unit::update(sf::Time time) {
    if (!isMoving) {
        return;
    }
    moving(time);
}

void unit::reset() {

}

void unit::moving(sf::Time time) {
    chooseUnit();
    if (!moveOver) {
        checkLeft();
        checkRight();
        checkUp();
        checkBottom();
        return;
    }
    auto motion = time.asMilliseconds() * speed;
    moveToLeft(motion);
    moveToRight(motion);
    moveToUp(motion);
    moveToBottom(motion);
}

void unit::checkMouse(sf::Mouse::Button button) {
    auto mouseIsPressed = sf::Mouse::isButtonPressed(button);
    if (mouseIsPressed) {
        auto mousePos = sf::Vector2f(sf::Mouse::getPosition(*renWin));
        auto unitCirc = getCircle();
        auto isMouseOverObj = unitCirc.getGlobalBounds().contains(mousePos);
        if (isMouseOverObj) {
            isPressed = true;
            return;
        }
        isPressed = false;
        return;
    }
}

void unit::chooseUnit() {
    if (!isPressed) {
        auto tempCirc = getCircle();
        tempCirc.setOutlineColor(sf::Color::Black);
        tempCirc.setOutlineThickness(1.0f);
        setCircle(tempCirc);
        return;
    }
    auto tempCirc = getCircle();
    tempCirc.setOutlineColor(sf::Color::Green);
    tempCirc.setOutlineThickness(5.0f);
    setCircle(tempCirc);
}

void unit::checkLeft() {
    if (!isPressed) {
        return;
    }
    auto isPressedA = sf::Keyboard::isKeyPressed(sf::Keyboard::A);
    if (isPressedA) {
        dir = eDirection::Left;
        nextPosX = getX() - getRadius() * 2 - 4;
        moveOver = true;
        std::cout << nextPosX << std::endl;
    }
}

void unit::checkRight() {
    if (!isPressed) {
        return;
    }
    auto isPressedD = sf::Keyboard::isKeyPressed(sf::Keyboard::D);
    if (isPressedD) {
        dir = eDirection::Right;
        nextPosX = getX() + getRadius() * 2 + 4;
        moveOver = true;
        std::cout << nextPosX << std::endl;
    }
}

void unit::checkUp() {
    if (!isPressed) {
        return;
    }
    auto isPressedW = sf::Keyboard::isKeyPressed(sf::Keyboard::W);
    if (isPressedW) {
        dir = eDirection::Up;
        nextPosY = getY() - getRadius() * 2 - 4;
        moveOver = true;
        std::cout << nextPosY << std::endl;
    }
}

void unit::checkBottom() {
    if (!isPressed) {
        return;
    }
    auto isPressedS = sf::Keyboard::isKeyPressed(sf::Keyboard::S);
    if (isPressedS) {
        dir = eDirection::Bottom;
        nextPosY = getY() + getRadius() * 2 + 4;
        moveOver = true;
        std::cout << nextPosY << std::endl;
    }
}

void unit::moveToLeft(float motion) {
//    if (nextPosX <= 200.f) {
//        moveOver = false;
//        nextPosX = 0;
//        dir = eDirection::Nowhere;
//        return;
//    }
    if (dir == eDirection::Left) {
        if (moveOver) {
            auto curUnitPosX = getX();
            if (curUnitPosX > nextPosX) {
                setX(curUnitPosX - motion);
                return;
            }
            setX(nextPosX);
            moveOver = false;
            nextPosX = 0;
            dir = eDirection::Nowhere;
            return;
        }
    }
}

void unit::moveToRight(float motion) {
//    if (nextPosX >= 950.f) {
//        moveOver = false;
//        nextPosX = 0;
//        dir = eDirection::Nowhere;
//        return;
//    }
    if (dir == eDirection::Right) {
        if (moveOver) {
            auto curUnitPosX = getX();
            if (curUnitPosX < nextPosX) {
                setX(curUnitPosX + motion);
                return;
            }
            setX(nextPosX);
            moveOver = false;
            nextPosX = 0;
            dir = eDirection::Nowhere;
            return;
        }
    }
}

void unit::moveToUp(float motion) {
//    if (nextPosY <= 150.f) {
//        moveOver = false;
//        nextPosY = 0;
//        dir = eDirection::Nowhere;
//        return;
//    }
    if(dir == eDirection::Up) {
        if (moveOver) {
            auto curUnitPosY = getY();
            if (curUnitPosY > nextPosY) {
                setY(curUnitPosY - motion);
                return;
            }
            setY(nextPosY);
            moveOver = false;
            nextPosY = 0;
            dir = eDirection::Nowhere;
            return;
        }
    }
}

void unit::moveToBottom(float motion) {
//    if (nextPosY >= 820.f) {
//        moveOver = false;
//        nextPosY = 0;
//        dir = eDirection::Nowhere;
//        return;
//    }
    if (dir == eDirection::Bottom) {
        if (moveOver) {
            auto curUnitPosY = getY();
            if (curUnitPosY < nextPosY) {
                setY(curUnitPosY + motion);
                return;
            }
            setY(nextPosY);
            moveOver = false;
            nextPosY = 0;
            dir = eDirection::Nowhere;
            return;
        }
    }
}

void unit::setIsMoving(bool state) {
    isMoving = state;
}
