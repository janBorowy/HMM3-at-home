#pragma once
#include <vector>
#include "SoldierTypes.h"
constexpr int ONE_FIELD_MOVEMENT_PENALTY = 100;

enum MilitaryUnit { Archer, Pikeman, SwordsMan };

struct UnitInfo {
    MilitaryUnit unit;
    int number;
    UnitInfo(MilitaryUnit u, int n) : unit(u), number(n) {}
};

class HeroResources {
    int stamina_;
    int gold_;
    int wood_;
    int ore_;
    const int movement_;
    int mana_;
    std::vector<UnitInfo> units_;

   public:
    HeroResources(int movement);
    int refreshStamina();
    int stamina() const;
    int movement() const;
    void reduceStaminaByStep();
    bool canMove() const;
    int calculateMaxSteps() const;
    int gold() const;
    int wood() const;
    int ore() const;
    void addGold(int);
    void addWood(int);
    void addOre(int);
};