#include "BattleButton.h"
#include "Label.h"

BattleButton::BattleButton(const Renderer &renderer, int width, int height)
    : Button("Next turn", renderer, "longboard.png", width, height) {}

void BattleButton::handleClick() {}