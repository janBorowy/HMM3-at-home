#include "Hero.h"
#include "MapObject.h"
#include "ShortestPathFinder.h"

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
    if (!canMove(destination, map, true)) {
        throw HeroException("Illegal move");
    }
    ShortestPathFinder finder(position_, destination);
    finder.visit(map);
    auto result = finder.result();
    resources_.reduceStaminaByNSteps(result.size() - 1);
    position_ = result.back();
}

std::vector<Position> Hero::getMovementPath(const Position &destination,
                                            const GameMap &map) const {
    ShortestPathFinder finder(position_, destination);
    finder.visit(map);
    return finder.result();
}

Position Hero::position() const { return position_; }

HeroResources &Hero::resources() { return resources_; }

bool Hero::canMove(const Position &destination, const GameMap &map,
                   bool isFinalDestination) const {
    if (destination.first < 0 || destination.first > map.width() ||
        destination.second < 0 || destination.second > map.height()) {
        return false;
    }

    if (!map.at(destination).movable(isFinalDestination) &&
        map.at(destination).object_.type() == MapObject::Type::ENEMY) {
        return true;
    }

    ShortestPathFinder finder(position_, destination);
    try {
        finder.visit(map);
    } catch (ShortestPathFinderException &e) {
        return false;
    }
    auto result = finder.result();
    int staminaRequired = (result.size() - 1) * ONE_FIELD_MOVEMENT_PENALTY;
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