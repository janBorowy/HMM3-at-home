#pragma once

#include <iostream>
#include <map>
#include <memory>
#include <vector>
#include "AlivePlayer.h"
#include "HeroResources.h"
#include "Player.h"
#include "SoldierTypes.h"

constexpr int COLS = 16;
constexpr int ROWS = 16;

enum BattleState { heroTurn, enemyTurn, won, lost };

class Battle {
    BattleState state_;
    int hero_paw_nr_;
    int enemy_paw_nr_;
    int counter_;

    std::vector<SoldierPtr> hero_army_;
    std::vector<SoldierPtr> enemy_army_;

    std::unique_ptr<Player> hero_;
    std::unique_ptr<Player> enemy_;

   public:
    Battle();
    ~Battle() = default;
    void battleSpin(int x, int y);
    void updateState();
    void setArmy(std::vector<UnitInfo> &hero_units,
                 std::vector<UnitInfo> &enemy_units);
    bool setHeroCounter(int counter);
    bool setEnemyCounter(int counter);
    BattleState getState();
    std::vector<SoldierPtr> &getHeroArmy();
    std::vector<SoldierPtr> &getEnemyArmy();
    int getCounter();
};