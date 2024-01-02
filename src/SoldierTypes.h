#pragma once
#include <memory>
#include "Soldier.h"

namespace SType {

class Archer : public Soldier {
   public:
    Archer(int number, int startX, int startY)
        : Soldier(6, 3, 3, 10, 10, 4, number, startX, startY, ARCHER) {}
    Archer(const Archer &other)
        : Soldier(6, 3, 3, 10, other.current_health_, 4, other.number_,
                  other.pos_x_, other.pos_y_, ARCHER) {}

    virtual int attack(int x, int y) override { return damage_ * number_; }
    virtual void loadSprites() override {
        auto image = GameData::getImage("ArcherRight.png");
        rightSprite_.reset(
            new Sprite(image->getWidth(), image->getHeight(), image));
        image = GameData::getImage("ArcherLeft.png");
        leftSprite_.reset(
            new Sprite(image->getWidth(), image->getHeight(), image));
        image = GameData::getImage("ArcherDead.png");
        deadSprite_.reset(
            new Sprite(image->getWidth(), image->getHeight(), image));
    }
    virtual SoldierPtr clone() const { return std::make_unique<Archer>(*this); }
};

class Pikeman : public Soldier {
   public:
    Pikeman(int number, int startX, int startY)
        : Soldier(4, 5, 3, 10, 10, 4, number, startX, startY, PIKEMAN) {}
    Pikeman(const Pikeman &other)
        : Soldier(4, 5, 3, 10, other.current_health_, 4, other.number_,
                  other.pos_x_, other.pos_y_, PIKEMAN) {}
    virtual void loadSprites() override {
        auto image = GameData::getImage("PikemanRight.png");
        rightSprite_.reset(
            new Sprite(image->getWidth(), image->getHeight(), image));
        image = GameData::getImage("PikemanLeft.png");
        leftSprite_.reset(
            new Sprite(image->getWidth(), image->getHeight(), image));
        image = GameData::getImage("PikemanDead.png");
        deadSprite_.reset(
            new Sprite(image->getWidth(), image->getHeight(), image));
    }
    virtual SoldierPtr clone() const {
        return std::make_unique<Pikeman>(*this);
    }
};

class SwordsMan : public Soldier {
   public:
    SwordsMan(int number, int startX, int startY)
        : Soldier(10, 12, 8, 35, 35, 5, number, startX, startY, SWORDSMAN) {}
    SwordsMan(const SwordsMan &other)
        : Soldier(10, 12, 8, 35, other.current_health_, 5, other.number_,
                  other.pos_x_, other.pos_y_, SWORDSMAN) {}
    virtual void loadSprites() override {
        auto image = GameData::getImage("SwordsmanRight.png");
        rightSprite_.reset(
            new Sprite(image->getWidth(), image->getHeight(), image));
        image = GameData::getImage("SwordsmanLeft.png");
        leftSprite_.reset(
            new Sprite(image->getWidth(), image->getHeight(), image));
        image = GameData::getImage("SwordsmanDead.png");
        deadSprite_.reset(
            new Sprite(image->getWidth(), image->getHeight(), image));
    }
    virtual SoldierPtr clone() const {
        return std::make_unique<SwordsMan>(*this);
    }
};

}  // namespace SType