#include "SpriteComponent.h"

SpriteComponent::SpriteComponent(std::string path,
                                 std::shared_ptr<Renderer> const &renderer)
    : sprite_(Sprite::loadFromPng(path, renderer->getSDLRenderer())) {}

SpriteComponent::SpriteComponent(Sprite sprite) : sprite_(new Sprite(sprite)) {}

void SpriteComponent::update(RendererPtr const &renderer,
                             PositionComponentPtr &positionComponent) {
    renderer->renderSprite(sprite_, positionComponent->getX(),
                           positionComponent->getY());
}
unsigned int SpriteComponent::getW() { return sprite_->getWidth(); }
unsigned int SpriteComponent::getH() { return sprite_->getHeight(); }

GraphicsComponent *SpriteComponent::clone() const {
    return new SpriteComponent(*sprite_);
};
