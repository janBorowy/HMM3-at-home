#pragma once
#include "Soldier.h"

namespace SType {

class Archer : public Soldier {
   public:
    Archer(int number, int startX, int startY)
        : Soldier(6, 3, 3, 10, 4, number, startX, startY, ARCHER) {
            auto image = GameData::getImage("ArcherRight.png");
            rightSprite_.reset(new Sprite(image->getWidth(), image->getHeight(), image));
            image = GameData::getImage("ArcherLeft.png");
            leftSprite_.reset(new Sprite(image->getWidth(), image->getHeight(), image));
            image = GameData::getImage("ArcherDead.png");
            deadSprite_.reset(new Sprite(image->getWidth(), image->getHeight(), image));
        }
    virtual int attack(int x, int y) override { return damage_ * number_; }
};

class Pikeman : public Soldier {
   public:
    Pikeman(int number, int startX, int startY)
        : Soldier(4, 5, 3, 10, 4, number, startX, startY, PIKEMAN) {
            auto image = GameData::getImage("PikemanRight.png");
            rightSprite_.reset(new Sprite(image->getWidth(), image->getHeight(), image));
            image = GameData::getImage("PikemanLeft.png");
            leftSprite_.reset(new Sprite(image->getWidth(), image->getHeight(), image));
            image = GameData::getImage("PikemanDead.png");
            deadSprite_.reset(new Sprite(image->getWidth(), image->getHeight(), image));
        }
};

class SwordsMan : public Soldier {
   public:
    SwordsMan(int number, int startX, int startY)
        : Soldier(10, 12, 8, 35, 5, number, startX, startY, SWORDSMAN) {
            auto image = GameData::getImage("SwordsmanRight.png");
            rightSprite_.reset(new Sprite(image->getWidth(), image->getHeight(), image));
            image = GameData::getImage("SwordsmanLeft.png");
            leftSprite_.reset(new Sprite(image->getWidth(), image->getHeight(), image));
            image = GameData::getImage("SwordsmanDead.png");
            deadSprite_.reset(new Sprite(image->getWidth(), image->getHeight(), image));
        }
};

}  // namespace SType