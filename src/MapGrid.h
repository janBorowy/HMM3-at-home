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

   public:
    MapGrid(unsigned short initX, unsigned short initY, unsigned short widht,
            unsigned short height);
    void drawFields(Renderer const &renderer) const;
    unsigned short x_;
    unsigned short y_;
};