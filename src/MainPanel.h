#pragma once
#include "MapExtrinsic.h"
#include "Panel.h"
#include "imgui.h"

struct MainPanel : public Panel {
    MainPanel();
    virtual void step();
    virtual void draw(Renderer const &renderer);
    virtual void drawImGui(Renderer const &renderer);
    virtual bool keyDown(SDL_Keycode key, Uint16 mod, bool isNewPress) override;
    virtual bool mouseButtonDown(int x, int y) override;

   private:
    MapExtrinsic map_;
};