#pragma once
#include "Button.h"
#include "Hero.h"

class NextTurnButton : public Button {
    Hero &hero_;

   public:
    NextTurnButton(Renderer const &renderer, int width, int height, Hero &hero);
    virtual void handleClick() override;
};