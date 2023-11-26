#pragma once

#include <array>
#include "Field.h"
#include "GameEntity.h"
#include "Renderer.h"

constexpr int GRID_WIDTH = 16;
constexpr int GRID_HEIGHT = 16;
using Fields = std::array<Field, GRID_HEIGHT * GRID_WIDTH>;

class MapGrid {
    Fields fields_;
    unsigned short x_;
    unsigned short y_;
    unsigned short width_;
    unsigned short height_;
    unsigned short fieldHeight_;
    unsigned short fieldWidth_;
    unsigned short selectedRow_;
    unsigned short selectedCol_;

   public:
    MapGrid(unsigned short initX, unsigned short initY, unsigned short widht,
            unsigned short height);
    void drawFields(Renderer const &renderer) const;
    void handleClick(int x, int y);
    Field &at(int row, int col);
};