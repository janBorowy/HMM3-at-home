#include "GameEntity.h"

GameEntity::GameEntity(GraphicsComponent *graphicsComponent)
    : graphicsComponent_(GraphicsComponentPtr(graphicsComponent)),
      positionComponent_(PositionComponentPtr(new PositionComponent)) {}

GameEntity::GameEntity(GraphicsComponent *graphicsComponent,
                       PositionComponent *positionComponent)
    : graphicsComponent_(GraphicsComponentPtr(graphicsComponent)),
      positionComponent_(PositionComponentPtr(positionComponent)) {}

void GameEntity::render(RendererPtr &renderer) {
    graphicsComponent_->update(renderer, positionComponent_);
}