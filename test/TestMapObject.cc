#include "../src/MapObject.h"
#include "doctest.h"

TEST_CASE("MapObject") {
    MapObject object(MapObject::GOLD, 1000);
    SUBCASE("Should initialize properly") {}
    SUBCASE("Should return correct type") {
        CHECK_EQ(object.type(), MapObject::GOLD);
    }
    SUBCASE("Should return correct value") { CHECK_EQ(object.value(), 1000); }
}