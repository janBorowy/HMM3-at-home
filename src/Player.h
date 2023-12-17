#pragma once

#include <memory>
#include <vector>
#include "Soldier.h"

using SoldierPtr = std::unique_ptr<Soldier>;
class Player {
   protected:
    int itr_;

   public:
    Player() : itr_(0) {}
    virtual bool makeMove(int x, int y, std::vector<SoldierPtr> &my_army,
                          std::vector<SoldierPtr> &enemy_army, int paw_nr) = 0;
};