#include "../src/GameMap.h"
#include "doctest.h"

TEST_CASE("GameMap") {
    auto gameMap = GameMap(20, 20);
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
        MapObject object(MapObject::GOLD, 500);
        gameMap.placeObject(10, 10, object);
        object = MapObject(MapObject::WOOD, 250);
        gameMap.placeObject(20, 20, object);
        auto &field = gameMap.at(10, 10);
        CHECK_EQ(field.object_.type(), MapObject::GOLD);
        CHECK_EQ(field.object_.value(), 500);
        field = gameMap.at(20, 20);
        CHECK_EQ(field.object_.type(), MapObject::WOOD);
        CHECK_EQ(field.object_.value(), 250);
    }
    SUBCASE("Should throw if trying to place object OOB") {
        MapObject object(MapObject::GOLD, 1000);
        CHECK_THROWS_AS(gameMap.placeObject(21, 21, object), GameMapException);
    }
}