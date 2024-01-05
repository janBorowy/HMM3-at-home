#include "SoldierTypes.h"

SType::Archer::Archer(int number, int startX, int startY)
    : Soldier(6, 3, 3, 10, 10, 4, number, startX, startY, ARCHER) {}
SType::Archer::Archer(const Archer &other)
    : Soldier(6, 3, 3, 10, other.current_health_, 4, other.number_,
              other.pos_x_, other.pos_y_, ARCHER) {}

int SType::Archer::attack(int x, int y) { return damage_ * number_; }
void SType::Archer::loadSprites() {
    auto image = GameData::getImage("ArcherRight.png");
    rightSprite_.reset(
        new Sprite(image->getWidth(), image->getHeight(), image));
    image = GameData::getImage("ArcherLeft.png");
    leftSprite_.reset(new Sprite(image->getWidth(), image->getHeight(), image));
    image = GameData::getImage("ArcherDead.png");
    deadSprite_.reset(new Sprite(image->getWidth(), image->getHeight(), image));
}
SoldierPtr SType::Archer::clone() const {
    return std::make_unique<Archer>(*this);
}

SType::Pikeman::Pikeman(int number, int startX, int startY)
    : Soldier(4, 5, 3, 10, 10, 4, number, startX, startY, PIKEMAN) {}
SType::Pikeman::Pikeman(const Pikeman &other)
    : Soldier(4, 5, 3, 10, other.current_health_, 4, other.number_,
              other.pos_x_, other.pos_y_, PIKEMAN) {}
void SType::Pikeman::loadSprites() {
    auto image = GameData::getImage("PikemanRight.png");
    rightSprite_.reset(
        new Sprite(image->getWidth(), image->getHeight(), image));
    image = GameData::getImage("PikemanLeft.png");
    leftSprite_.reset(new Sprite(image->getWidth(), image->getHeight(), image));
    image = GameData::getImage("PikemanDead.png");
    deadSprite_.reset(new Sprite(image->getWidth(), image->getHeight(), image));
}
SoldierPtr SType::Pikeman::clone() const {
    return std::make_unique<Pikeman>(*this);
}

SType::SwordsMan::SwordsMan(int number, int startX, int startY)
    : Soldier(10, 12, 8, 35, 35, 5, number, startX, startY, SWORDSMAN) {}
SType::SwordsMan::SwordsMan(const SwordsMan &other)
    : Soldier(10, 12, 8, 35, other.current_health_, 5, other.number_,
              other.pos_x_, other.pos_y_, SWORDSMAN) {}
void SType::SwordsMan::loadSprites() {
    auto image = GameData::getImage("SwordsmanRight.png");
    rightSprite_.reset(
        new Sprite(image->getWidth(), image->getHeight(), image));
    image = GameData::getImage("SwordsmanLeft.png");
    leftSprite_.reset(new Sprite(image->getWidth(), image->getHeight(), image));
    image = GameData::getImage("SwordsmanDead.png");
    deadSprite_.reset(new Sprite(image->getWidth(), image->getHeight(), image));
}
SoldierPtr SType::SwordsMan::clone() const {
    return std::make_unique<SwordsMan>(*this);
}

SType::Minotaur::Minotaur(int number, int startX, int startY)
    : Soldier(14, 12, 16, 50, 50, 6, number, startX, startY, MINOTAUR) {}
SType::Minotaur::Minotaur(const Minotaur &other)
    : Soldier(14, 12, 16, 50, other.current_health_, 6, other.number_,
              other.pos_x_, other.pos_y_, MINOTAUR) {}
void SType::Minotaur::loadSprites() {
    auto image = GameData::getImage("MinotaurRight.png");
    rightSprite_.reset(
        new Sprite(image->getWidth(), image->getHeight(), image));
    image = GameData::getImage("MinotaurLeft.png");
    leftSprite_.reset(new Sprite(image->getWidth(), image->getHeight(), image));
    image = GameData::getImage("MinotaurDead.png");
    deadSprite_.reset(new Sprite(image->getWidth(), image->getHeight(), image));
}
SoldierPtr SType::Minotaur::clone() const {
    return std::make_unique<Minotaur>(*this);
}

SType::Troglodyte::Troglodyte(int number, int startX, int startY)
    : Soldier(4, 3, 2, 5, 5, 4, number, startX, startY, TROGLODYTE) {}
SType::Troglodyte::Troglodyte(const Troglodyte &other)
    : Soldier(4, 3, 2, 5, other.current_health_, 4, other.number_, other.pos_x_,
              other.pos_y_, TROGLODYTE) {}
void SType::Troglodyte::loadSprites() {
    auto image = GameData::getImage("TroglodyteRight.png");
    rightSprite_.reset(
        new Sprite(image->getWidth(), image->getHeight(), image));
    image = GameData::getImage("TroglodyteLeft.png");
    leftSprite_.reset(new Sprite(image->getWidth(), image->getHeight(), image));
    image = GameData::getImage("TroglodyteDead.png");
    deadSprite_.reset(new Sprite(image->getWidth(), image->getHeight(), image));
}
SoldierPtr SType::Troglodyte::clone() const {
    return std::make_unique<Troglodyte>(*this);
}

SType::Beholder::Beholder(int number, int startX, int startY)
    : Soldier(6, 3, 3, 10, 10, 4, number, startX, startY, BEHOLDER) {}
SType::Beholder::Beholder(const Beholder &other)
    : Soldier(6, 3, 3, 10, other.current_health_, 4, other.number_,
              other.pos_x_, other.pos_y_, BEHOLDER) {}
int SType::Beholder::attack(int x, int y) { return damage_ * number_; }
void SType::Beholder::loadSprites() {
    auto image = GameData::getImage("BeholderRight.png");
    rightSprite_.reset(
        new Sprite(image->getWidth(), image->getHeight(), image));
    image = GameData::getImage("BeholderLeft.png");
    leftSprite_.reset(new Sprite(image->getWidth(), image->getHeight(), image));
    image = GameData::getImage("BeholderDead.png");
    deadSprite_.reset(new Sprite(image->getWidth(), image->getHeight(), image));
}
SoldierPtr SType::Beholder::clone() const {
    return std::make_unique<Beholder>(*this);
}