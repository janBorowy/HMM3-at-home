#pragma once
#include "Hero.h"

class TurnManager {
    Hero &playerHero_;
    unsigned int currentTurn_;

   public:
    TurnManager(Hero &playerHero);
    void nextTurn();
    unsigned int currentTurn() const;
};