#include "HeroResources.h"

namespace {
int calculateStamina(int movement) { return movement; }
constexpr int ONE_FIELD_MOVEMENT_PENALTY = 100;
};  // namespace

HeroResources::HeroResources(int movement)
    : stamina_(calculateStamina(0)), movement_(movement) {}

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

bool HeroResources::canMove() const { return stamina_ != 0; }
int HeroResources::calculateMaxSteps() const {
    auto staminaLeft = calculateStamina(movement_);
    auto fields = staminaLeft / ONE_FIELD_MOVEMENT_PENALTY;
    if (staminaLeft % ONE_FIELD_MOVEMENT_PENALTY > 0) ++fields;
    return fields;
}