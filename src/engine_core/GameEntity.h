#pragma once
#include <memory>
#include "components/GraphicsComponent.h"
#include "components/PositionComponent.h"
#include "components/StateComponent.h"

class GameEntity {
   protected:
    GraphicsComponentPtr graphicsComponent_;
    PositionComponentPtr positionComponent_;
    StateComponentPtr stateComponent_;

   public:
    GameEntity(GraphicsComponent *graphicsComponent);
    GameEntity(GraphicsComponent *graphicsComponent,
               PositionComponent *positionComponent);
    virtual ~GameEntity();
    StateComponentPtr getState();
    void setClickState(StateComponent::ClickState state);
    virtual void render(RendererPtr &renderer);
    void setPosition(unsigned x, unsigned y);
    unsigned clicked_x;
    unsigned clicked_y;
    virtual void clickedCallback();
    SDL_Rect getPosition();
    void update();
};