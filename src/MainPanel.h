#pragma once
#include "Panel.h"

struct MainPanel : public Panel {
    MainPanel();
    virtual void step();
    virtual void draw(Renderer &renderer);
    virtual bool keyDown(SDL_Keycode key, Uint16 mod, Command const &command,
                         bool isNewPress) override;
};