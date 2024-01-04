#include "BattleButton.h"
#include "Label.h"

BattleButton::BattleButton(const Renderer &renderer, int width, int height)
    : Button("Next turn", renderer, "woodButton.png", width, height) {}

void BattleButton::handleClick() {}