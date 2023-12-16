#include "NextTurnButton.h"

NextTurnButton::NextTurnButton(const Renderer &renderer, int width, int height,
                               TurnManager &turnManager)
    : Button("Next turn", renderer, width, height), turnManager_(turnManager) {}

void NextTurnButton::handleClick() { turnManager_.nextTurn(); }