#include "../src/MapParser.h"
#include "../src/ShortestPathFinder.h"
#include "doctest.h"

TEST_CASE("ShortestPathFinder") {
    MapParser parser(5, 5);
    auto finder = ShortestPathFinder({1, 1}, {5, 5});
    SUBCASE("One Path is correct") {
        /*
        0 0 W 0 0
        W 0 0 W 0
        W W 0 0 W
        W W W 0 0
        W W W W 0
        */
        std::istringstream stream(std::string("0 0 W 0 0 ") + "W 0 0 W 0 " +
                                  "W W 0 0 W " + "W W W 0 0 " + "W W W W 0 ");
        auto map = parser.parse(stream);
        finder.visit(map);
        CHECK_EQ(finder.result(), std::vector<Position>{{1, 1},
                                                        {2, 1},
                                                        {2, 2},
                                                        {3, 2},
                                                        {3, 3},
                                                        {4, 3},
                                                        {4, 4},
                                                        {5, 4},
                                                        {5, 5}});
    }
    SUBCASE("Blocked in center") {
        /*
        0 0 0 0 0
        0 W W W 0
        0 W W W 0
        0 W W W 0
        0 0 0 0 0
        */
        std::istringstream stream(std::string("0 0 0 0 0 ") + "0 W W W 0 " +
                                  "0 W W W 0 " + "0 W W W 0 " + "0 0 0 0 0 ");
        auto map = parser.parse(stream);
        finder.visit(map);
        CHECK(finder.result() == std::vector<Position>{{1, 1},
                                                       {2, 1},
                                                       {3, 1},
                                                       {4, 1},
                                                       {5, 1},
                                                       {5, 2},
                                                       {5, 3},
                                                       {5, 4},
                                                       {5, 5}});
    }
}