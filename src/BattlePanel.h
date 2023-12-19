#pragma once

#include "Battle.h"
// #include "BattleExtrinsic.h"
// #include "Label.h"
// #include "NextTurnButton.h"
#include "GameData.h"
#include "Panel.h"
#include "TurnManager.h"
#include "imgui.h"

struct BattlePanel : public Panel {
   public:
    Renderer const &renderer_;
    BattlePanel(Renderer const &renderer);
    virtual void step();
    virtual void draw();
    virtual void drawImGui();
    virtual bool keyDown(SDL_Keycode key, Uint16 mod, bool isNewPress) override;
    virtual bool mouseButtonDown(int x, int y) override;

   private:
    Battle battle_;
    int x_;
    int y_;
    int clicked_col_;
    int clicked_row_;

    SpriteUPtr selectedFieldSprite_;
    SpriteUPtr emptyFieldSprite_;
    SpriteUPtr battleGroundSprite_;
    SpriteUPtr blueFieldSprite_;
    SpriteUPtr whiteFieldSprite_;

    void handleMapGridClick(int col, int row);
    // void handleMapGridSelect(int col, int row);
    void loadBattleSprites();
    void drawWalkingDistance(int x, int y, int distance);
};