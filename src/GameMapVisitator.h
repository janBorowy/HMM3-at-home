#include "GameMap.h"

class GameMapVisitator {
   public:
    void virtual visit(GameMap const &map) = 0;
};