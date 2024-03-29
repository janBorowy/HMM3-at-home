#pragma once
#include "BuyUnitButton.h"
#include "HeroExtrinsic.h"
#include "HeroResources.h"
#include "Label.h"
#include "MapExtrinsic.h"
#include "NextTurnButton.h"
#include "Panel.h"
#include "SelectionVisitator.h"
#include "TurnManager.h"
#include "UI.h"
#include "imgui.h"

enum Difficulty { easy, normal, hard };
struct MainPanel : public Panel {
    const Renderer &renderer_;
    MainPanel(const Renderer &renderer);
    virtual void step();
    virtual void draw();
    virtual void drawImGui();
    virtual bool keyDown(SDL_Keycode key, Uint16 mod, bool isNewPress) override;
    virtual bool mouseButtonDown(int x, int y) override;
    void setDifficulty(Difficulty difficulty);

   private:
    Difficulty difficulty_;
    MapExtrinsic map_;
    Label staminaResourceLabel_;
    Label goldResourceLabel_;
    Label woodResourceLabel_;
    Label oreResourceLabel_;
    Label turnLabel_;
    Label unitInfoLabel_;
    SelectionVisitator selection_;
    HeroExtrinsic playerHero_;
    TurnManager turnManager_;
    NextTurnButton nextTurnButton_;
    BuyUnitButton buyPikemanButton_;
    BuyUnitButton buyArcherButton_;
    BuyUnitButton buySwordsmanButton_;

    SpriteUPtr background_;

    void handleMapGridClick(int col, int row);
    void handleMapGridSelect(int col, int row);
    void handleMapGridMove(int col, int row);
    void updateAndDrawLabels();
    void setBattle(int mapCol, int mapRow);
};