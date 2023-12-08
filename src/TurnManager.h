#pragma once
#include "Hero.h"

class TurnManager {
    Hero &playerHero_;

   public:
    TurnManager(Hero &playerHero);
    void nextTurn();
};