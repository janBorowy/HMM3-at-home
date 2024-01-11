#pragma once
#include "MainPanel.h"

class DifficultyButton : public Button {
    Difficulty difficulty_;

   public:
    DifficultyButton(const Renderer &renderer, int width, int height,
                     Difficulty difficulty);
    virtual void handleClick() override;
};