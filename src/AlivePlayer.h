#pragma once
#include "Player.h"

class AlivePlayer : public Player {
    int8_t game_grid[16][16];
    int my_x_;
    int my_y_;

   public:
    AlivePlayer() : Player() {}
    virtual bool makeMove(int x, int y, std::vector<SoldierPtr> &my_army,
                          std::vector<SoldierPtr> &enemy_army,
                          int paw_nr) override;
    bool tryToAttack(int x, int y);
    bool tryToMove(int x, int y, int distance);
    std::pair<int, int> calculateRoute(int x, int y);
};