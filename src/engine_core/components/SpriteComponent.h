#pragma once
#include "GraphicsComponent.h"
#include "../Sprite.h"

class SpriteComponent : public GraphicsComponent {
    std::unique_ptr<Sprite> sprite_;
    public:
    virtual ~SpriteComponent() = default;
    SpriteComponent(std::string path, std::unique_ptr<Renderer> &renderer);
    virtual void update(std::unique_ptr<Renderer> &renderer);
};