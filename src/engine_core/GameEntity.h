#pragma once
#include <memory>
#include "components/GraphicsComponent.h"
#include "components/PositionComponent.h"
#include "components/StateComponent.h"

class GameEntity {
    GraphicsComponentPtr graphicsComponent_;
    PositionComponentPtr positionComponent_;
    StateComponentPtr stateComponent_;

   public:
    GameEntity(GraphicsComponent *graphicsComponent);
    GameEntity(GraphicsComponent *graphicsComponent,
               PositionComponent *positionComponent);
    StateComponentPtr getState();
    void setClickState(StateComponent::ClickState state);
    void render(RendererPtr &renderer);
    void setPosition(unsigned int x, unsigned int y);
    SDL_Rect getPosition();
    GameEntity clone() const;
    void update();
};