#pragma once

#include "Battle.h"
#include "BattleButton.h"
#include "GameData.h"
#include "Panel.h"
#include "TurnManager.h"
#include "imgui.h"

struct BattlePanel : public Panel {
   public:
    const Renderer &renderer_;
    BattlePanel(const Renderer &renderer, std::vector<UnitInfo> &hero_units,
                std::vector<UnitInfo> &enemy_units);
    virtual void step();
    virtual void draw();
    virtual void drawImGui();
    virtual bool keyDown(SDL_Keycode key, Uint16 mod, bool isNewPress) override;
    virtual bool mouseButtonDown(int x, int y) override;
    void setArmies(std::vector<UnitInfo> &hero_units,
                   std::vector<UnitInfo> &enemy_units);

   private:
    std::vector<UnitInfo> &hero_initial_army_;
    Battle battle_;
    bool if_soldier_info_;
    int x_;
    int y_;
    int clicked_col_;
    int clicked_row_;

    BattleButton button_;

    SpriteUPtr selectedFieldSprite_;
    SpriteUPtr emptyFieldSprite_;
    SpriteUPtr battleGroundSprite_;
    SpriteUPtr blueFieldSprite_;
    SpriteUPtr whiteFieldSprite_;
    SpriteUPtr panel_;
    SpriteUPtr wonSprite_;
    SpriteUPtr lostSprite_;

    void handleMapGridClick(int col, int row);

    void loadBattleSprites();
    void drawWalkingDistance(int x, int y, int distance);
    void drawSoldierInfo(const SoldierPtr &soldier);
};