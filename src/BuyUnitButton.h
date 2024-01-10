#pragma once
#include "Button.h"
#include "Soldier.h"
#include "TurnManager.h"

class BuyUnitButton : public Button {
    ArmyBranch branch_;
    ResourceType resourceType_;
    HeroResources &heroResources_;
    int quantity_;
    int cost_;

   public:
    BuyUnitButton(const Renderer &renderer, int width, int height,
                  HeroResources &resources);
    void setBuyDetails(int cost, ResourceType type, ArmyBranch branch,
                       int quantity);
    virtual void handleClick() override;
};