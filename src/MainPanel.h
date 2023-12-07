#pragma once
#include "HeroExtrinsic.h"
#include "Label.h"
#include "MapExtrinsic.h"
#include "Panel.h"
#include "SelectionVisitator.h"
#include "imgui.h"

struct MainPanel : public Panel {
    Renderer const &renderer_;
    MainPanel(Renderer const &renderer);
    virtual void step();
    virtual void draw();
    virtual void drawImGui();
    virtual bool keyDown(SDL_Keycode key, Uint16 mod, bool isNewPress) override;
    virtual bool mouseButtonDown(int x, int y) override;

   private:
    MapExtrinsic map_;
    Label staminaResourceLabel_;
    Label goldResourceLabel_;
    Label woodResourceLabel_;
    Label oreResourceLabel_;
    SelectionVisitator selection_;
    HeroExtrinsic playerHero_;

    void handleMapGridClick(int col, int row);
    void handleMapGridSelect(int col, int row);
    void handleMapGridMove(int col, int row);
};