#pragma once

#include <iostream>
#include <map>
#include <memory>
#include <vector>
#include "HeroResources.h"
#include "SoldierTypes.h"

#define Cols 16
#define Rows 16

enum BattleState { heroTurn, enemyTurn, won, lost };

using SoldierPtr = std::unique_ptr<Soldier>;

class Battle {
    std::map<int, SoldierPtr> enemy_;
    std::map<int, SoldierPtr> hero_;

    std::vector<int> enemy_keys_;
    std::vector<int> hero_keys_;

    BattleState state_;
    int paw_counter_;

    int game_grid[Rows][Cols];

   public:
    Battle(std::vector<UnitInfo> &hero_units,
           std::vector<UnitInfo> &enemy_units);
    ~Battle() = default;
    void battle_spin(int x, int y);
    void print_grid();
    void update_grid();
    void clear_grid();
};