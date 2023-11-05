#include "SpriteComponent.h"

SpriteComponent::SpriteComponent(std::string path,
                                 std::unique_ptr<Renderer> &renderer)
    : sprite_(Sprite::loadFromPng(path, renderer->getSDLRenderer())) {}

void SpriteComponent::update(RendererPtr &renderer,
                             PositionComponentPtr &positionComponent) {
    renderer->renderSprite(sprite_, positionComponent->getX(),
                           positionComponent->getY());
}