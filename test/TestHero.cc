#include "../src/Hero.h"
#include "doctest.h"

TEST_CASE("Hero") {
    Hero hero(0, 0);
    GameMap map;
    SUBCASE("Should initialize properly") {}
    SUBCASE("Should get correct position") {
        auto pos = hero.position();
        CHECK_EQ(pos, Position{0, 0});
    }
    SUBCASE("Should move to given position") {
        hero.move(Position{2, 2}, map);
        auto pos = hero.position();
        auto stamina = hero.resources().stamina();
        CHECK_EQ(pos, Position{2, 2});
        CHECK_EQ(stamina,
                 INITIAL_HERO_MOVEMENT - 4 * ONE_FIELD_MOVEMENT_PENALTY);
        hero.move(Position{7, 8}, map);
        pos = hero.position();
        stamina = hero.resources().stamina();
        CHECK_EQ(pos, Position{7, 8});
        CHECK_EQ(stamina, 0);
    }
    SUBCASE("Should not be possible to move out of bounds") {
        CHECK_THROWS_AS(hero.move(Position{-1, -1}, map), HeroException);
        auto fartherHero = Hero(MAP_WIDTH, MAP_HEIGHT);
        CHECK_THROWS_AS(
            fartherHero.move(Position{MAP_WIDTH + 1, MAP_HEIGHT + 1}, map),
            HeroException);
    }
    SUBCASE("Should not be able to move if not enough stamina") {
        CHECK_THROWS_AS(hero.move(Position{MAP_WIDTH, MAP_HEIGHT}, map),
                        HeroException);
        CHECK_THROWS_AS(hero.move(Position{8, 8}, map), HeroException);
    }
}