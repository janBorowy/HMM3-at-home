#include "SpriteComponent.h"

SpriteComponent::SpriteComponent(std::string path, std::unique_ptr<Renderer> &renderer):
    sprite_(Sprite::loadFromPng(path, renderer->getSDLRenderer())) {}

void SpriteComponent::update(std::unique_ptr<Renderer> &renderer) {
    renderer->renderSprite(sprite_, 600, 400);
}