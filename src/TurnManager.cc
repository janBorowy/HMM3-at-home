#include "TurnManager.h"

TurnManager::TurnManager(Hero &playerHero)
    : playerHero_(playerHero), currentTurn_(1) {}

void TurnManager::nextTurn() {
    ++currentTurn_;
    playerHero_.resources().refreshStamina();
}

unsigned int TurnManager::currentTurn() const { return currentTurn_; }