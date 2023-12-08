#pragma once
#include "Button.h"
#include "TurnManager.h"

class NextTurnButton : public Button {
    TurnManager &turnManager_;

   public:
    NextTurnButton(Renderer const &renderer, int width, int height,
                   TurnManager &turnManager);
    virtual void handleClick() override;
};