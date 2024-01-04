#pragma once
#include "Button.h"

class BattleButton : public Button {
   public:
    BattleButton(const Renderer &renderer, int width, int height);
    virtual void handleClick() override;
};