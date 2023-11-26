#pragma once
#include "MapGrid.h"
#include "Panel.h"

struct MainPanel : public Panel {
    MainPanel();
    virtual void step();
    virtual void draw(Renderer const &renderer);
    virtual bool keyDown(SDL_Keycode key, Uint16 mod, bool isNewPress) override;

   private:
    MapGrid mapGrid_;
};