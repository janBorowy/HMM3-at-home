#include "GameEntity.h"

GameEntity::GameEntity(GraphicsComponent *graphicsComponent)
    : graphicsComponent_(GraphicsComponentPtr(graphicsComponent)),
      positionComponent_(PositionComponentPtr(new PositionComponent)),
      state_(DEFAULT) {}

GameEntity::GameEntity(GraphicsComponent *graphicsComponent,
                       PositionComponent *positionComponent)
    : graphicsComponent_(GraphicsComponentPtr(graphicsComponent)),
      positionComponent_(PositionComponentPtr(positionComponent)),
      state_(DEFAULT) {}

void GameEntity::render(RendererPtr &renderer) {
    graphicsComponent_->update(renderer, positionComponent_);
}

State GameEntity::getState() { return state_; }

void GameEntity::setState(State state) { state_ = state; }

SDL_Rect GameEntity::getPosition() {
    SDL_Rect rect;
    rect.x = positionComponent_->getX();
    rect.y = positionComponent_->getY();
    rect.w = graphicsComponent_->getW();
    rect.h = graphicsComponent_->getH();
    return rect;
}