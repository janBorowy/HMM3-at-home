#include "GameMap.h"

namespace {}  // namespace

GameMap::GameMap() : fields_() { initFields(); }

void GameMap::initFields() {
    for (auto &row : fields_) {
        for (auto &field : row) {
            field = MapField(MapObject(MapObject::Type::NONE, 0), true);
        }
    }
}

Fields const &GameMap::fields() const { return fields_; }

void GameMap::placeObject(int x, int y, MapObject object) {
    fields_[y - 1][x - 1].object_ = object;
}