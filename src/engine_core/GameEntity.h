#pragma once
#include <memory>
#include "components/GraphicsComponent.h"

class GameEntity {

    std::unique_ptr<GraphicsComponent> graphicsComponent_;

    public:
    GameEntity(GraphicsComponent *renderComponent);
    void render(std::unique_ptr<Renderer> &renderer);
};