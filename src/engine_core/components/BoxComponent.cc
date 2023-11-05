#include "BoxComponent.h"

BoxComponent::BoxComponent(unsigned int size) : size_(size) {}

unsigned int BoxComponent::getW() { return size_; }

unsigned int BoxComponent::getH() { return size_; }

void BoxComponent::update(RendererPtr &renderer,
                          PositionComponentPtr &posititonComponent) {
    unsigned int x = posititonComponent->getX();
    unsigned int y = posititonComponent->getY();

    renderer->drawLine(x, y, x + size_, y);
    renderer->drawLine(x, y, x, y + size_);
    renderer->drawLine(x + size_, y, x + size_, y + size_);
    renderer->drawLine(x, y + size_, x + size_, y + size_);
}