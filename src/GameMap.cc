#include "GameMap.h"

namespace {}  // namespace

GameMap::GameMap(unsigned short width, unsigned short height)
    : width_(width),
      height_(height),
      fields_(height,
              std::vector<MapField>(
                  width, MapField(MapObject(MapObject::Type::NONE, 0), true))) {
}

Fields const &GameMap::fields() const { return fields_; }

void GameMap::placeObject(int col, int row, MapObject const &object) {
    checkInBounds(col, row);
    at(col, row).object_ = object;
}

void GameMap::checkInBounds(int col, int row) const {
    if (col < 0 || col > width_ || row < 0 || row > height_) {
        throw GameMapException("Tried to place object out of bounds");
    }
}

unsigned short GameMap::width() const { return width_; }
unsigned short GameMap::height() const { return height_; }
MapField &GameMap::at(int col, int row) {
    checkInBounds(col, row);
    return fields_[row - 1][col - 1];
}
MapField const &GameMap::at(int col, int row) const {
    checkInBounds(col, row);
    return fields_[row - 1][col - 1];
}