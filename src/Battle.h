#pragma once

#include <iostream>
#include <map>
#include <memory>
#include <vector>
#include "AiPlayer.h"
#include "AlivePlayer.h"
#include "HeroResources.h"
#include "Player.h"
#include "SoldierTypes.h"

// constexpr int COLS = 16;
// constexpr int ROWS = 16;

enum BattleState { heroTurn, enemyTurn, waitForNextTurn, won, lost };

class Battle {
    BattleState state_;
    int hero_paw_nr_;
    int enemy_paw_nr_;
    int counter_;
    bool ai_enemy_;

    std::vector<SoldierPtr> hero_army_;
    std::vector<SoldierPtr> enemy_army_;

    std::unique_ptr<Player> hero_;
    std::unique_ptr<Player> enemy_;

    void pushToArmyVector(std::vector<SoldierPtr> &vec, ArmyBranch type,
                          int num, int x, int y);

   public:
    Battle(bool ai_game);
    ~Battle() = default;
    void battleSpin(int x, int y);
    void updateState();
    void handleNextTurn();
    void setArmy(std::vector<UnitInfo> &hero_units,
                 std::vector<UnitInfo> &enemy_units);
    void loadArmySprites();
    bool setHeroCounter(int counter);
    bool setEnemyCounter(int counter);
    BattleState getState();
    std::vector<SoldierPtr> &getHeroArmy();
    std::vector<SoldierPtr> &getEnemyArmy();
    int getCounter();
};