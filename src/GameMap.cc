#include "GameMap.h"

namespace {}  // namespace

GameMap::GameMap() : fields_() { initFields(); }

void GameMap::initFields() {
    for (auto &row : fields_) {
        for (auto &field : row) {
            field = MapField(1, true);
        }
    }
}