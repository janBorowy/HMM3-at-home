#include "Hero.h"

Hero::Hero(int initialX, int initialY)
    : resources_(INITIAL_HERO_MOVEMENT), position_(initialX, initialY) {}

void Hero::move(Position const &destination, GameMap const &map) {
    if (destination.first < 0 || destination.first > map.width() ||
        destination.second < 0 || destination.second > map.height()) {
        throw HeroException("Illegal move destination");
    }

    Position delta;
    delta.first = destination.first - position_.first;
    delta.second = destination.second - position_.second;
    int staminaRequired =
        (abs(delta.first) + abs(delta.second)) * ONE_FIELD_MOVEMENT_PENALTY;
    if (resources_.stamina() < staminaRequired) {
        throw HeroException("Not enough stamina");
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

HeroResources const &Hero::resources() const { return resources_; }