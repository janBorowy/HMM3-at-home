#pragma once
#include "components/GraphicsComponent.h"
#include "components/PositionComponent.h"
#include <memory>

enum State { DEFAULT = 0, IS_CLICKED = 1 };

class GameEntity {
  GraphicsComponentPtr graphicsComponent_;
  PositionComponentPtr positionComponent_;
  State state_;

public:
  GameEntity(GraphicsComponent *graphicsComponent);
  GameEntity(GraphicsComponent *graphicsComponent,
             PositionComponent *positionComponent);
  State getState();
  void setState(State state);
  void render(RendererPtr &renderer);
  SDL_Rect getPosition();
};