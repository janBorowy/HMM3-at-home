#include "BuyUnitButton.h"

BuyUnitButton::BuyUnitButton(const Renderer &renderer, int width, int height,
                             HeroResources &resources)
    : Button("Buy soldier", renderer, width, height),
      heroResources_(resources) {}

void BuyUnitButton::setBuyDetails(int cost, ResourceType type,
                                  ArmyBranch branch, int quantity) {
    cost_ = cost;
    resourceType_ = type;
    quantity_ = quantity;
    branch_ = branch;
    updateText("Buy " + std::to_string(quantity_) + " " +
               Soldier::branchToString(branch_));
}

void BuyUnitButton::handleClick() {
    if (heroResources_.getResource(resourceType_) < cost_) {
        return;
    }
    heroResources_.addResource(resourceType_, -cost_);
    heroResources_.addUnit(branch_, quantity_);
}