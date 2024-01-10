#pragma once
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
};