#pragma once
#include <memory>
#include "Soldier.h"

namespace SType {

class Archer : public Soldier {
   public:
    Archer(int number, int startX, int startY);
    Archer(const Archer &other);
    virtual int attack(int x, int y) override;
    virtual void loadSprites() override;
    SoldierPtr clone() const;
};

class Pikeman : public Soldier {
   public:
    Pikeman(int number, int startX, int startY);
    Pikeman(const Pikeman &other);
    virtual void loadSprites() override;
    virtual SoldierPtr clone() const;
};

class SwordsMan : public Soldier {
   public:
    SwordsMan(int number, int startX, int startY);
    SwordsMan(const SwordsMan &other);
    virtual void loadSprites() override;
    virtual SoldierPtr clone() const;
};

class Minotaur : public Soldier {
   public:
    Minotaur(int number, int startX, int startY);
    Minotaur(const Minotaur &other);
    virtual void loadSprites() override;
    virtual SoldierPtr clone() const;
};

class Troglodyte : public Soldier {
   public:
    Troglodyte(int number, int startX, int startY);
    Troglodyte(const Troglodyte &other);
    virtual void loadSprites() override;
    virtual SoldierPtr clone() const;
};

class Beholder : public Soldier {
   public:
    Beholder(int number, int startX, int startY);
    Beholder(const Beholder &other);
    virtual int attack(int x, int y) override;
    virtual void loadSprites() override;
    SoldierPtr clone() const;
};
}  // namespace SType