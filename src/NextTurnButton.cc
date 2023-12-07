#include "NextTurnButton.h"

NextTurnButton::NextTurnButton(Renderer const &renderer, int width, int height,
                               Hero &hero)
    : Button("Next turn", renderer, width, height), hero_(hero) {}

void NextTurnButton::handleClick() { hero_.nextTurn(); }