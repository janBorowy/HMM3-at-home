#pragma once
#include <array>
#include "MapField.h"

constexpr int MAP_WIDTH = 200;
constexpr int MAP_HEIGHT = 200;

using Fields = std::array<std::array<MapField, MAP_WIDTH>, MAP_HEIGHT>;
class GameMap {
    Fields fields_;
    void initFields();

   public:
    GameMap();
};