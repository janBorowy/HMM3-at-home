#include "EmptyComponent.h"

EmptyComponent::EmptyComponent() : width_(0), height_(0) {}
EmptyComponent::EmptyComponent(unsigned width, unsigned height)
    : width_(width), height_(height) {}
void EmptyComponent::update(RendererPtr const &renderer,
                            PositionComponentPtr &positionComponent) {}
unsigned EmptyComponent::getW() { return width_; }
unsigned EmptyComponent::getH() { return height_; }