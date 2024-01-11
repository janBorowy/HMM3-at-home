#pragma once
#include "DifficultyButton.h"
#include "GameData.h"
#include "Label.h"
#include "Panel.h"

struct StartPanel : public Panel {
    const Renderer &renderer_;
    StartPanel(const Renderer &renderer);
    virtual void step();
    virtual void draw();
    virtual void drawImGui();
    virtual bool keyDown(SDL_Keycode key, Uint16 mod, bool isNewPress) override;
    virtual bool mouseButtonDown(int x, int y) override;

   private:
    SpriteUPtr front_page_;

    DifficultyButton easy_button_;
    DifficultyButton normal_button_;
    DifficultyButton hard_button_;
};