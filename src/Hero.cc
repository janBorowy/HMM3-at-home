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

void Hero::move(const Position &destination, const GameMap &map) {
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

std::vector<Position> Hero::getMovementPath(const Position &destination,
                                            const GameMap &map) const {
    if (!canMove(destination, map)) {
        throw HeroException("Illegal move");
    }
    auto position = position_;
    std::vector<Position> traveledPath;
    while (resources_.canMove() && position != destination) {
        traveledPath.push_back(position);
        if (position.first < destination.first) {
            ++(position.first);
            continue;
        } else if (position.first > destination.first) {
            --(position.first);
            continue;
        } else if (position.second < destination.second) {
            ++(position.second);
            continue;
        } else {
            --(position.second);
            continue;
        }
    }
    traveledPath.push_back(position);
    return traveledPath;
}

Position Hero::position() const { return position_; }

HeroResources &Hero::resources() { return resources_; }

bool Hero::canMove(const Position &destination, const GameMap &map) const {
    if (destination.first < 0 || destination.first > map.width() ||
        destination.second < 0 || destination.second > map.height() ||
        !map.at(destination).movable()) {
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

void Hero::interactWith(GameMap &map, const Position &position) {
    auto &object = map.at(position.first, position.second).object_;
    switch (object.type()) {
        case MapObject::NONE:
            break;
        case MapObject::GOLD:
            resources_.addGold(object.value());
            break;
        case MapObject::WOOD:
            resources_.addWood(object.value());
            break;
        case MapObject::ORE:
            resources_.addOre(object.value());
            break;
    }
    object = MapObject(MapObject::NONE, 0);
}