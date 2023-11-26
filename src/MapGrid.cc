#include "MapGrid.h"
#include "initializer_list"

MapGrid::MapGrid(unsigned short initX, unsigned short initY,
                 unsigned short width, unsigned short height)
    : fields_{}, x_(initX), y_(initY) {
    auto fieldHeight = height / GRID_HEIGHT;
    auto fieldWidth = width / GRID_WIDTH;

    for (int y = 0; y < GRID_HEIGHT; ++y) {
        for (int x = 0; x < GRID_WIDTH; ++x) {
            fields_[y * GRID_HEIGHT + x] =
                Field(initX + fieldWidth * x, initY + fieldHeight * y,
                      fieldWidth, fieldHeight);
        }
    }
}

void MapGrid::drawFields(Renderer const &renderer) const {
    for (auto &field : fields_) {
        renderer.drawEntity(field);
    }
}