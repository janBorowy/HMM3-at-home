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

GameEntity::GameEntity(GraphicsComponent *graphicsComponent,
                       PositionComponent *positionComponent)
    : graphicsComponent_(GraphicsComponentPtr(graphicsComponent)),
      positionComponent_(PositionComponentPtr(positionComponent)) {}

void GameEntity::render(RendererPtr &renderer) {
<<<<<<< HEAD
    graphicsComponent_->update(renderer, positionComponent_);
=======
    graphicsComponent_->update(renderer, positionComponent_);
>>>>>>> 0734a40 (prototype of event handler function added)
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