#include "../GameDefaults.h"
#include "BoxEntity.h"
#include "GridEntity.h"
#include "components/BoxComponent.h"
#include "components/EmptyComponent.h"
GridEntity::GridEntity()
    : GameEntity(new EmptyComponent(
          GRID_DIMENSIONS::SQUARE_SIZE * GRID_DIMENSIONS::COLUMNS,
          GRID_DIMENSIONS::SQUARE_SIZE * GRID_DIMENSIONS::ROWS)),
      boxes_() {
    unsigned count = 0;
    for (unsigned row = 0; row < GRID_DIMENSIONS::ROWS; ++row) {
        boxes_.push_back(std::vector<std::unique_ptr<GameEntity>>());
        for (unsigned col = 0; col < GRID_DIMENSIONS::COLUMNS; ++col) {
            boxes_[row].push_back(std::unique_ptr<GameEntity>(new BoxEntity(
                new PositionComponent(col * GRID_DIMENSIONS::SQUARE_SIZE,
                                      row * GRID_DIMENSIONS::SQUARE_SIZE))));
            ++count;
        }
    }
}
GridEntity::~GridEntity() {}

void GridEntity::clickedCallback() {
    unsigned row =
        (clicked_y - positionComponent_->getY()) / GRID_DIMENSIONS::SQUARE_SIZE;
    unsigned col =
        (clicked_x - positionComponent_->getX()) / GRID_DIMENSIONS::SQUARE_SIZE;
    boxes_[row][col]->clickedCallback();
    stateComponent_->clicked = StateComponent::DEFAULT;
}

void GridEntity::render(RendererPtr &renderer) {
    for (auto &row : boxes_)
        for (auto &box : row) {
            box->render(renderer);
        }
}