#include "../src/TurnManager.h"
#include "doctest.h"

TEST_CASE("TurnManager") {
    GameMap map(10, 10);
    Hero playerHero(1, 1);
    TurnManager manager(playerHero);
    SUBCASE("Should initialize properly") {}
    SUBCASE("Should refresh hero stamina") {
        playerHero.move({2, 2}, map);
        manager.nextTurn();
        CHECK_EQ(playerHero.resources().stamina(), 1500);
    }
}