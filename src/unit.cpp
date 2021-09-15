#include "unit.h"

void unit::init() {
    setID("unit_");
    setRadius(60.0f);
    setAnchor(0.5f, 0.5f);
    state = eState::Start;
}

void unit::update(sf::Time time) {

}

void unit::edgeCollision() {


}

void unit::reset() {

}

void unit::moving(sf::Time time) {

}
