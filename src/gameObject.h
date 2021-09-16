#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include "mainController.h"

enum class eState {
    Stop,
    Start,
    Collision
};

class gameObject {
public:
    virtual void init() = 0;
    inline std::string getID() const {return id;}
    inline void setID(std::string _id) {id += _id;}
    inline float getX() const {return posX;}
    inline void setX(float _x) {
        posX = _x;
        circle.setPosition(posX, posY);
    }
    inline float getY() const {return posY;}
    inline void setY(float _y) {
        posY = _y;
        circle.setPosition(posX, posY);
    }
    inline sf::Vector2f getXY() const {return {posX, posY};}
    inline void setXY(float _x, float _y) {
        posX = _x;
        posY = _y;
        circle.setPosition(posX, posY);
    }
    inline sf::Vector2f getStartPos() const {return startPos;}
    inline void setStartPos(float _x, float _y) {
        startPos = {_x, _y};
        posX = _x;
        posY = _y;
        circle.setPosition(startPos);
    }
    inline float getRadius() const {return circle.getRadius();}
    inline void setRadius(float _radius) {circle.setRadius(_radius);}
    inline sf::CircleShape getCircle() const {return circle;}
    inline std::pair<float, float> const getAnchor() {return std::pair<float, float> (aX, aY);}
    inline float getAnchorX() {return aX;}
    inline float getAnchorY() {return aY;}
    inline void setAnchor(float _aX, float _aY) {
        aX = _aX;
        aY = _aY;
        circle.setOrigin(aX, aY);
    }
    inline void setAcnhorX(float _aX) {
        aX = _aX;
        circle.setOrigin(aX, aY);
    }
    inline void setAcnhorY(float _aY) {
        aY = _aY;
        circle.setOrigin(aX, aY);
    }
    inline void setController(MainController* controller) {mController = controller;}
    inline MainController* getController() {return mController;}
    inline sf::Color getColor() {return circle.getFillColor();}
    inline void setColor(sf::Color _color) {circle.setFillColor(_color);}
    inline float getHeight() {return circle.getLocalBounds().height;}
    inline float getWidth() {return circle.getLocalBounds().width;}
    inline float getLeft() {return circle.getLocalBounds().left;}
    inline float getTop() {return circle.getLocalBounds().top;}
    inline void setWindow(sf::RenderWindow* _window) {renWin = _window;}
    virtual void render() {renWin->draw(circle);}
    virtual void update(sf::Time time) = 0;
protected:
    sf::RenderWindow* renWin;
    eState state;
private:
    std::string id;
    float posX;
    float posY;
    float aX;
    float aY;
    sf::Vector2f startPos;
    sf::CircleShape circle;
    MainController* mController;
};
