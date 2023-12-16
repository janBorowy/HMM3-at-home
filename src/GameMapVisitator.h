#include "GameMap.h"

class GameMapVisitator {
   public:
    void virtual visit(const GameMap &map) = 0;
};