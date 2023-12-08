#pragma once
#include <stdexcept>
#include <utility>
#include "GameMap.h"
#include "HeroResources.h"
using Position = std::pair<int, int>;

constexpr int INITIAL_HERO_MOVEMENT = 1500;

class HeroException : public std::runtime_error {
   public:
    HeroException(std::string const &msg) : std::runtime_error(msg) {}
};

class Hero {
    HeroResources resources_;
    Position position_;

   public:
    Hero(int initialCol, int initialRow);
    Position position() const;
    HeroResources &resources();
    void move(Position const &destination, GameMap const &map);
    bool canMove(Position const &destination, GameMap const &map) const;
    void interactWith(GameMap &map, Position const &at);
};