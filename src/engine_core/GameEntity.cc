#include "GameEntity.h"

GameEntity::GameEntity(
    GraphicsComponent *graphicsComponent
): graphicsComponent_(std::unique_ptr<GraphicsComponent>(graphicsComponent)) {}


void GameEntity::render(std::unique_ptr<Renderer> &renderer) {
    graphicsComponent_->update(renderer);
}