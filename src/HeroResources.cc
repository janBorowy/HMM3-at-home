#include "HeroResources.h"
#include "Soldier.h"

namespace {
int calculateStamina(int movement) { return movement; }
};  // namespace

HeroResources::HeroResources(int movement)
    : stamina_(calculateStamina(movement)),
      movement_(movement),
      gold_(0),
      wood_(0),
      ore_(0) {
    // Starting units
    units_.push_back(UnitInfo(ARCHER, 5));
    units_.push_back(UnitInfo(PIKEMAN, 10));
    units_.push_back(UnitInfo(SWORDSMAN, 3));
}

int HeroResources::refreshStamina() {
    stamina_ = calculateStamina(movement_);
    return stamina_;
}

int HeroResources::stamina() const { return stamina_; }
int HeroResources::movement() const { return movement_; }

void HeroResources::reduceStaminaByStep() {
    stamina_ -= ONE_FIELD_MOVEMENT_PENALTY;
    if (stamina_ < 0) stamina_ = 0;
}

void HeroResources::reduceStaminaByNSteps(int n) {
    while (n > 0) {
        reduceStaminaByStep();
        --n;
    }
}

bool HeroResources::canMove() const { return stamina_ != 0; }
int HeroResources::calculateMaxSteps() const {
    auto staminaLeft = calculateStamina(movement_);
    auto fields = staminaLeft / ONE_FIELD_MOVEMENT_PENALTY;
    if (staminaLeft % ONE_FIELD_MOVEMENT_PENALTY > 0) ++fields;
    return fields;
}

int HeroResources::gold() const { return gold_; }
int HeroResources::ore() const { return ore_; }
int HeroResources::wood() const { return wood_; }

void HeroResources::addGold(int delta) { gold_ += delta; }
void HeroResources::addWood(int delta) { wood_ += delta; }
void HeroResources::addOre(int delta) { ore_ += delta; }

std::vector<UnitInfo> &HeroResources::getUnits() { return units_; }

std::string UnitInfo::infoString() const {
    return Soldier::branchToString(unit) + ": " + std::to_string(number);
}

void HeroResources::addUnit(ArmyBranch branch, int quantity) {
    for (auto &unitInfo : units_) {
        if (unitInfo.unit == branch) {
            unitInfo.number += quantity;
            return;
        }
    }
    units_.push_back(UnitInfo(branch, quantity));
}

int HeroResources::getResource(ResourceType type) const {
    switch (type) {
        case GOLD:
            return gold();
        case WOOD:
            return wood();
        case ORE:
            return ore();
    }
    return 0;
}

void HeroResources::addResource(ResourceType type, int delta) {
    switch (type) {
        case GOLD:
            addGold(delta);
            break;
        case WOOD:
            addWood(delta);
            break;
        case ORE:
            addOre(delta);
            break;
    }
    return;
}