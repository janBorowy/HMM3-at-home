#include "MapGrid.h"
#include "initializer_list"

MapGrid::MapGrid(unsigned short initX, unsigned short initY,
                 unsigned short width, unsigned short height)
    : fields_{},
      x_{initX},
      y_{initY},
      fieldHeight_(height / GRID_HEIGHT),
      fieldWidth_(width / GRID_WIDTH) {
    for (int y = 0; y < GRID_HEIGHT; ++y) {
        for (int x = 0; x < GRID_WIDTH; ++x) {
            at(x + 1, y + 1) =
                Field(initX + fieldWidth_ * x, initY + fieldHeight_ * y,
                      fieldWidth_, fieldHeight_);
        }
    }
}

void MapGrid::drawFields(Renderer const &renderer) const {
    for (auto &field : fields_) {
        renderer.drawEntity(field);
    }
}

void MapGrid::handleClick(int x, int y) {
    auto gridX = (x - x_) / fieldWidth_ + 1;
    auto gridY = (y - y_) / fieldHeight_ + 1;
    at(gridX, gridY).changeSprite("selected_field.png");
}

Field &MapGrid::at(int col, int row) {
    return fields_[(row - 1) * GRID_WIDTH + (col - 1)];
}