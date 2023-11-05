#pragma once
#include <memory>
#include "components/GraphicsComponent.h"
#include "components/PositionComponent.h"

class GameEntity {
    GraphicsComponentPtr graphicsComponent_;
    PositionComponentPtr positionComponent_;

   public:
    GameEntity(GraphicsComponent *graphicsComponent);
    GameEntity(GraphicsComponent *graphicsComponent,
               PositionComponent *positionComponent);
    void render(RendererPtr &renderer);
};