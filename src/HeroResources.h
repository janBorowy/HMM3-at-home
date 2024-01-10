#pragma once
#include <vector>
#include "Soldier.h"
#include "SoldierTypes.h"
constexpr int ONE_FIELD_MOVEMENT_PENALTY = 100;

struct UnitInfo {
    ArmyBranch unit;
    int number;
    UnitInfo(ArmyBranch u, int n) : unit(u), number(n) {}
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
    void reduceStaminaByNSteps(int n);
    bool canMove() const;
    int calculateMaxSteps() const;
    int gold() const;
    int wood() const;
    int ore() const;
    void addGold(int);
    void addWood(int);
    void addOre(int);
    std::vector<UnitInfo> &getUnits();
};