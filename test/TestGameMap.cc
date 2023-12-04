#include "../src/GameMap.h"
#include "doctest.h"

TEST_CASE("GameMap") {
    SUBCASE("Should initialize properly") { auto gameMap = GameMap(); }
}