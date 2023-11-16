#include "BoxComponent.h"

BoxComponent::BoxComponent(unsigned int size) : size_(size), clicked_(false) {}

unsigned int BoxComponent::getW() { return size_; }

unsigned int BoxComponent::getH() { return size_; }

#include <iostream>
void BoxComponent::update(RendererPtr const &renderer,
                          PositionComponentPtr &positionComponent) {
    unsigned int x = positionComponent->getX();
    unsigned int y = positionComponent->getY();

    if (clicked_) {
        renderer->setColor(255, 0, 0);
    } else {
        renderer->setColor(0xFF, 0xFF, 0xFF);
    }

    renderer->drawLine(x, y, x + size_, y);
    renderer->drawLine(x, y, x, y + size_);
    renderer->drawLine(x + size_, y, x + size_, y + size_);
    renderer->drawLine(x, y + size_, x + size_, y + size_);
}