#include "../GameDefaults.h"
#include "BoxEntity.h"
#include "components/BoxComponent.h"

BoxEntity::BoxEntity(PositionComponent *positionComponent)
    : GameEntity(new BoxComponent(GRID_DIMENSIONS::SQUARE_SIZE),
                 positionComponent) {}
BoxEntity::~BoxEntity() {}

#include <iostream>
void BoxEntity::clickedCallback() {
    auto boxComponent = new BoxComponent(GRID_DIMENSIONS::SQUARE_SIZE);
    boxComponent->clicked_ = true;
    graphicsComponent_.reset(boxComponent);
    stateComponent_->clicked = StateComponent::DEFAULT;
}