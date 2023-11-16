#pragma once
#include "GameEntity.h"
class BoxEntity : public GameEntity {
   public:
    BoxEntity(PositionComponent *positionComponent);
    virtual ~BoxEntity() override;
    virtual void clickedCallback() override;
};