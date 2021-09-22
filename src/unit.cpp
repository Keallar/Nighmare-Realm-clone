#include "unit.h"
#include "gameController.h"
#include <iostream>

void unit::init() {
    setID("unit_");
    setRadius(60.0f);
    state = eState::Start;
    speed = 0.3;
    isPressed = false;
    isMoving = false;
    moveOver = false;
    dir = eDirection::Nowhere;
    nextPosX = 0;
    prevPosX = 0;
    nextPosY = 0;
    prevPosY = 0;
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
            //std::cout << mousePos.x << " " << mousePos.y << std::endl;
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
        prevPosX = getX();
        moveOver = true;
        //std::cout << nextPosX << std::endl;
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
        prevPosX = getX();
        moveOver = true;
        //std::cout << nextPosX << std::endl;
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
        prevPosY = getY();
        moveOver = true;
        //std::cout << nextPosY << std::endl;
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
        prevPosY = getY();
        moveOver = true;
        //std::cout << nextPosY << std::endl;
    }
}

void unit::moveToLeft(float motion) {
    if (dir == eDirection::Left) {
        //auto isCollBlockCell = dynamic_cast<gameController*>(getController())->collWithBlockedCell(this);
        auto isCollOtherUnit = dynamic_cast<gameController*>(getController())->collWithOtherUnit(this);
        if (/*isCollBlockCell ||*/ isCollOtherUnit) {
            moveOver = false;
            setX(prevPosX);
            prevPosX = 0;
            nextPosX = 0;
            dir = eDirection::Nowhere;
            std::cout << "Blocked Left" << std::endl;
            return;
        }
        if (nextPosX <= 172.f) {
            moveOver = false;
            nextPosX = 0;
            dir = eDirection::Nowhere;
            return;
        }
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
    if (dir == eDirection::Right) {
        auto isCollBlockCell = dynamic_cast<gameController*>(getController())->collWithBlockedCell(this);
        if (isCollBlockCell) {
            moveOver = false;
            setX(prevPosX);
            prevPosX = 0;
            nextPosX = 0;
            dir = eDirection::Nowhere;
            std::cout << "Blocked Right" << std::endl;
            return;
        }
        if (nextPosX >= 952.f) {
            moveOver = false;
            nextPosX = 0;
            dir = eDirection::Nowhere;
            return;
        }
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
    if(dir == eDirection::Up) {
        auto isCollBlockCell = dynamic_cast<gameController*>(getController())->collWithBlockedCell(this);
        if (isCollBlockCell) {
            moveOver = false;
            setY(prevPosY);
            prevPosY = 0;
            nextPosX = 0;
            dir = eDirection::Nowhere;
            std::cout << "Blocked Up" << std::endl;
            return;
        }
        if (nextPosY <= 72.f) {
            moveOver = false;
            nextPosY = 0;
            dir = eDirection::Nowhere;
            return;
        }
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
    if (dir == eDirection::Bottom) {
        auto isCollBlockCell = dynamic_cast<gameController*>(getController())->collWithBlockedCell(this);
        if (isCollBlockCell) {
            moveOver = false;
            setY(prevPosY);
            prevPosY = 0;
            nextPosX = 0;
            dir = eDirection::Nowhere;
            std::cout << "Blocked Bottom" << std::endl;
            return;
        }
        if (nextPosY >= 820.f) {
            moveOver = false;
            nextPosY = 0;
            dir = eDirection::Nowhere;
            return;
        }
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

int unit::getNextPosX(){
    return nextPosX;
}

int unit::getNextPosY() {
    return nextPosY;
}

int unit::getPrevPosX() {
    return prevPosX;
}

int unit::getPrevPosY() {
    return prevPosY;
}
