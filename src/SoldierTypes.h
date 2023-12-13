#pragma once
#include "Soldier.h"

namespace SType {

class Archer : public Soldier {
   public:
    Archer(int number, int startX, int startY)
        : Soldier(6, 3, 3, 10, 4, number, startX, startY) {}
    virtual int attack(int x, int y) override { return damage_ * number_; }
};

class Pikeman : public Soldier {
   public:
    Pikeman(int number, int startX, int startY)
        : Soldier(4, 5, 3, 10, 4, number, startX, startY) {}
};

class SwordsMan : public Soldier {
   public:
    SwordsMan(int number, int startX, int startY)
        : Soldier(10, 12, 8, 35, 5, number, startX, startY) {}
};

}  // namespace SType