#include "../src/HeroResources.h"
#include "doctest.h"

TEST_CASE("HeroResources") {
    HeroResources heroResources = HeroResources(1500);
    SUBCASE("Should initialize properly") {
        auto heroResources = HeroResources(1500);
        CHECK_EQ(heroResources.stamina(), 1500);
    }
    SUBCASE("Should refresh stamina properly") {
        heroResources.refreshStamina();
        CHECK_EQ(heroResources.stamina(), 1500);
    }
    SUBCASE("Should reduce stamina correctly") {
        heroResources.refreshStamina();
        heroResources.reduceStaminaByStep();
        CHECK_EQ(heroResources.stamina(), 1400);
    }
    SUBCASE("Should not reduce stamina to lower than 0") {
        auto heroResources = HeroResources(1450);
        for (int i = 0; i < 15; ++i) {
            heroResources.reduceStaminaByStep();
        }
        CHECK_EQ(heroResources.stamina(), 0);
    }
    SUBCASE("Should count max steps correctly") {
        CHECK_EQ(heroResources.calculateMaxSteps(), 15);
        auto moreStaminaHeroResources = HeroResources(1544);
        CHECK_EQ(moreStaminaHeroResources.calculateMaxSteps(), 16);
    }
}