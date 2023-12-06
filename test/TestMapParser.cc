#include <sstream>
#include "../src/MapParser.h"
#include "doctest.h"

TEST_CASE("MapParser") {
    std::istringstream stream("0 0 0 g(1000) w(500) o(750) 0 0 0");
    MapParser parser(3, 3);
    SUBCASE("Should initialize properly") {}
    SUBCASE("Throw if illegal indentifier") {
        std::istringstream incorrectData("0 0 0 g(1000) h(500) o(750) 0 0 0");
        MapParser parser(3, 3);
        CHECK_THROWS_AS(parser.parse(incorrectData), MapParserException);
    }
    SUBCASE("Should parse given data correctly") {
        auto map = parser.parse(stream);
        CHECK_EQ(map.at(1, 1).object_.type(), MapObject::NONE);
        CHECK_EQ(map.at(3, 3).object_.type(), MapObject::NONE);
        CHECK_EQ(map.at(1, 2).object_.type(), MapObject::GOLD);
        CHECK_EQ(map.at(1, 2).object_.value(), 1000);
        CHECK_EQ(map.at(2, 2).object_.type(), MapObject::WOOD);
        CHECK_EQ(map.at(2, 2).object_.value(), 500);
        CHECK_EQ(map.at(3, 2).object_.type(), MapObject::ORE);
        CHECK_EQ(map.at(3, 2).object_.value(), 750);
    }
}