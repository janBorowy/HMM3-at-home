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
    Hero(int initialX, int initialY);
    Position position() const;
    HeroResources const &resources() const;
    void move(Position const &destination, GameMap const &map);
};