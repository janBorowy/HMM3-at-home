#include "GameEntity.h"

GameEntity::GameEntity(GraphicsComponent *graphicsComponent)
    : graphicsComponent_(GraphicsComponentPtr(graphicsComponent)),
      positionComponent_(PositionComponentPtr(new PositionComponent)),
      stateComponent_(StateComponentPtr(new StateComponent)) {}

GameEntity::GameEntity(GraphicsComponent *graphicsComponent,
                       PositionComponent *positionComponent)
    : graphicsComponent_(GraphicsComponentPtr(graphicsComponent)),
      positionComponent_(PositionComponentPtr(positionComponent)),
      stateComponent_(StateComponentPtr(new StateComponent())) {}

void GameEntity::render(RendererPtr &renderer) {
    graphicsComponent_->update(renderer, positionComponent_);
}

StateComponentPtr GameEntity::getState() { return stateComponent_; }

void GameEntity::setClickState(StateComponent::ClickState state) {
    stateComponent_->clicked = state;
}

void GameEntity::setPosition(unsigned int x, unsigned int y) {
    positionComponent_->setX(x);
    positionComponent_->setY(y);
}

SDL_Rect GameEntity::getPosition() {
    SDL_Rect rect;
    rect.x = positionComponent_->getX();
    rect.y = positionComponent_->getY();
    rect.w = graphicsComponent_->getW();
    rect.h = graphicsComponent_->getH();
    return rect;
}

GameEntity GameEntity::clone() const {
    auto positionComponentCopy(*positionComponent_);
    auto graphicsComponentCopy = graphicsComponent_->clone();
    return GameEntity(graphicsComponentCopy, &positionComponentCopy);
}
void GameEntity::update() {
    if (stateComponent_->clicked) {
        // call on click command
    }
    stateComponent_->clicked = StateComponent::ClickState::DEFAULT;
}