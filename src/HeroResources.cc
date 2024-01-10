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
    std::string unitName;
    switch (unit) {
        case ArmyBranch::ARCHER:
            unitName = "Archer";
            break;
        case ArmyBranch::PIKEMAN:
            unitName = "Pikeman";
            break;
        case ArmyBranch::SWORDSMAN:
            unitName = "Swordsman";
            break;
        default:
            unitName = "unknown";
    }

    return unitName + ": " + std::to_string(number);
}