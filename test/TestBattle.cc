#include "../src/Battle.h"
#include "doctest.h"

TEST_CASE("Battle") {
    SType::Archer archer(5, 0, 0);
    SType::Pikeman pikeman(5, 0, 0);
    SType::SwordsMan swordsMan(5, 0, 0);
    SUBCASE("Should initialize properly") {}
    SUBCASE("Testing initialization and methods") {
        CHECK_FALSE(archer.try_to_move(15, 15));
        CHECK_EQ(archer.attack(15, 15), 15);
        CHECK_EQ(pikeman.attack(15, 15), 0);
    }
    std::vector<UnitInfo> h_units;
    std::vector<UnitInfo> e_units;
    h_units.push_back(UnitInfo(Archer, 3));
    h_units.push_back(UnitInfo(Pikeman, 4));
    h_units.push_back(UnitInfo(SwordsMan, 1));

    e_units.push_back(UnitInfo(Archer, 5));
    e_units.push_back(UnitInfo(Pikeman, 5));
}