#pragma once
#include "Panel.h"

struct MainPanel : public Panel {
    MainPanel();
    virtual void step();
    virtual void draw(std::shared_ptr<Renderer> renderer);
    virtual bool keyDown(SDL_Keycode key, Uint16 mod, Command const &command,
                         bool isNewPress) override;
};