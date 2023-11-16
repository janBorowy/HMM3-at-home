#pragma once
#include <vector>
#include "GameEntity.h"

class GridEntity : public GameEntity {
    std::vector<std::vector<std::unique_ptr<GameEntity>>> boxes_;

   public:
    GridEntity();
    virtual ~GridEntity() override;
    virtual void clickedCallback() override;
    virtual void render(RendererPtr &renderer) override;
};