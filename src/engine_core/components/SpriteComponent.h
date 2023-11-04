#pragma once
#include "GraphicsComponent.h"
#include "../Sprite.h"
#include "PositionComponent.h"

class SpriteComponent : public GraphicsComponent {
    std::unique_ptr<Sprite> sprite_;
    public:
    virtual ~SpriteComponent() = default;
    SpriteComponent(std::string path, std::unique_ptr<Renderer> &renderer);
    virtual void update(std::unique_ptr<Renderer> &renderer, PositionComponentPtr &positionComponent);
    virtual unsigned int getW();
    virtual unsigned int getH();
};