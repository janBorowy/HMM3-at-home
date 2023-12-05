#include "../src/GameMap.h"
#include "doctest.h"

TEST_CASE("GameMap") {
    auto gameMap = GameMap();
    SUBCASE("Should initialize properly") {}
    SUBCASE("Should be initialized empty and boring") {
        auto &fields = gameMap.fields();
        for (auto &row : fields) {
            for (auto &field : row) {
                CHECK_EQ(field.object_.type(), MapObject::NONE);
                CHECK_EQ(field.object_.value(), 0);
            }
        }
    }
    SUBCASE("Should place objects properly") {
        MapObject object(MapObject::GOLD, 1000);
        gameMap.placeObject(10, 10, object);
        auto &field = gameMap.fields()[9][9];
        CHECK_EQ(field.object_.type(), MapObject::GOLD);
        CHECK_EQ(field.object_.value(), 1000);
    }
}