#pragma once
#include <array>
#include "MapField.h"

constexpr int MAP_WIDTH = 50;
constexpr int MAP_HEIGHT = 50;

using Fields = std::array<std::array<MapField, MAP_WIDTH>, MAP_HEIGHT>;
class GameMap {
    Fields fields_;
    void initFields();

   public:
    GameMap();
    Fields const &fields() const;
    void placeObject(int x, int y, MapObject object);
};