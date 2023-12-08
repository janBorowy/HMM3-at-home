#include "TurnManager.h"

TurnManager::TurnManager(Hero &playerHero) : playerHero_(playerHero) {}

void TurnManager::nextTurn() { playerHero_.resources().refreshStamina(); }