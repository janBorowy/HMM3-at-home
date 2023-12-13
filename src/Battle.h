#pragma once

#include <iostream>
#include <map>
#include <memory>
#include <vector>
#include "AlivePlayer.h"
#include "HeroResources.h"
#include "Player.h"
#include "SoldierTypes.h"

#define Cols 16
#define Rows 16

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
    Battle(std::vector<UnitInfo> &hero_units,
           std::vector<UnitInfo> &enemy_units);
    ~Battle() = default;
    void battleSpin(int x, int y);
    void updateState();
    BattleState getState();
};