#pragma once
#include "../Sprite.h"
#include "GraphicsComponent.h"
#include "PositionComponent.h"

class SpriteComponent : public GraphicsComponent {
    std::shared_ptr<Sprite> sprite_;
    SpriteComponent(Sprite sprite);

   public:
    virtual ~SpriteComponent() = default;
    SpriteComponent(std::string path,
                    std::shared_ptr<Renderer> const &renderer);
    virtual void update(std::shared_ptr<Renderer> const &renderer,
                        PositionComponentPtr &positionComponent);
    virtual unsigned int getW();
    virtual unsigned int getH();
    virtual GraphicsComponent *clone() const override;
};