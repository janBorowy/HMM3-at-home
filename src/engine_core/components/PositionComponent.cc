#include "PositionComponent.h"

PositionComponent::PositionComponent(): x_(0), y_(0) {}

PositionComponent::PositionComponent(unsigned int x, unsigned int y)
: x_(x), y_(y){}

void PositionComponent::setX(unsigned int x) {
    x_ = x;
}

void PositionComponent::setY(unsigned int y) {
    y_ = y;
}

unsigned int PositionComponent::getX() {
    return x_;
}

unsigned int PositionComponent::getY() {
    return y_;
}