#pragma once
#include <cmath>
#include "GameData.h"
#include "Sprite.h"

enum ArmyBranch { ARCHER, PIKEMAN, SWORDSMAN, MINOTAUR, TROGLODYTE, BEHOLDER };

class Soldier {
   public:
   protected:
    ArmyBranch type_;
    const int attack_;
    const int defense_;
    const int damage_;
    const int health_;
    const int walk_distance_;
    int current_health_;
    int number_;
    int pos_x_;
    int pos_y_;

   public:
    Soldier(int attack, int defense, int damage, int health, int current_health,
            int walk_distance, int number, int startX, int startY,
            ArmyBranch type);
    Soldier(const Soldier &other);
    void receive_damage(int damage);
    virtual int attack(int x, int y);
    bool try_to_move(int x, int y);
    int get_number();
    bool isAlive();
    int getX();
    int getY();
    int getWalk();
    int getCurrentHealth();
    int getDamage();
    int getHealth();
    void setNumber(int num);
    void setCurrentHealth(int health);
    void setX(int x);
    void setY(int y);
    ArmyBranch get_type() const;
    virtual std::unique_ptr<Soldier> clone() const = 0;

    virtual void loadSprites() = 0;

    SpriteUPtr rightSprite_;
    SpriteUPtr leftSprite_;
    SpriteUPtr deadSprite_;
};

using SoldierPtr = std::unique_ptr<Soldier>;