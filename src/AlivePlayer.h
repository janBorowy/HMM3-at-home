#pragma once
#include "Battle.h"
#include "Player.h"

constexpr int COLS = 16;
constexpr int ROWS = 16;
class AlivePlayer : public Player {
    int8_t game_grid[ROWS][COLS];
    int my_x_;
    int my_y_;

   public:
    AlivePlayer() : Player() {}
    virtual bool makeMove(int x, int y, std::vector<SoldierPtr> &my_army,
                          std::vector<SoldierPtr> &enemy_army, int paw_nr);
    bool tryToAttack(int x, int y);
    bool tryToMove(int x, int y, int distance);
    std::pair<int, int> calculateRoute(int x, int y);
};