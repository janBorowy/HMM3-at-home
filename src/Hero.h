#pragma once
#include <stdexcept>
#include <utility>
#include "GameMap.h"
#include "HeroResources.h"
using Position = std::pair<int, int>;

constexpr int INITIAL_HERO_MOVEMENT = 1500;

class HeroException : public std::runtime_error {
   public:
    HeroException(const std::string &msg) : std::runtime_error(msg) {}
};

class Hero {
    HeroResources resources_;
    Position position_;

   public:
    Hero(int initialCol, int initialRow);
    Position position() const;
    HeroResources &resources();
    void move(const Position &destination, const GameMap &map);
    std::vector<Position> getMovementPath(const Position &destination,
                                          const GameMap &map) const;
    bool canMove(const Position &destination, const GameMap &map) const;
    void interactWith(GameMap &map, const Position &at);
};