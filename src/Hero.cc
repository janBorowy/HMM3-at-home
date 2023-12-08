#include "Hero.h"

namespace {
constexpr int INITIAL_GOLD = 1000;
constexpr int INITIAL_WOOD = 500;
constexpr int INTIAL_ORE = 250;
}  // namespace

Hero::Hero(int initialCol, int initialRow)
    : resources_(INITIAL_HERO_MOVEMENT), position_(initialCol, initialRow) {
    resources_.addGold(INITIAL_GOLD);
    resources_.addWood(INITIAL_WOOD);
    resources_.addOre(INTIAL_ORE);
}

void Hero::move(Position const &destination, GameMap const &map) {
    if (!canMove(destination, map)) {
        throw HeroException("Illegal move");
    }

    while (resources_.canMove() && position_ != destination) {
        resources_.reduceStaminaByStep();
        if (position_.first < destination.first) {
            ++(position_.first);
            continue;
        } else if (position_.first > destination.first) {
            --(position_.first);
            continue;
        } else if (position_.second < destination.second) {
            ++(position_.second);
            continue;
        } else {
            --(position_.second);
            continue;
        }
    }
}

Position Hero::position() const { return position_; }

HeroResources &Hero::resources() { return resources_; }

bool Hero::canMove(Position const &destination, GameMap const &map) const {
    if (destination.first < 0 || destination.first > map.width() ||
        destination.second < 0 || destination.second > map.height()) {
        return false;
    }

    Position delta;
    delta.first = destination.first - position_.first;
    delta.second = destination.second - position_.second;
    int staminaRequired =
        (abs(delta.first) + abs(delta.second)) * ONE_FIELD_MOVEMENT_PENALTY;
    if (resources_.stamina() < staminaRequired) {
        return false;
    }
    return true;
}
