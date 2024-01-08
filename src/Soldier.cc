#include "Soldier.h"
#include <stdexcept>

Soldier::Soldier(int attack, int defense, int damage, int health,
                 int current_health, int walk_distance, int number, int startX,
                 int startY, ArmyBranch type)
    : attack_(attack),
      defense_(defense),
      damage_(damage),
      health_(health),
      walk_distance_(walk_distance),
      current_health_(current_health),
      number_(number),
      type_(type)

{
    if (startX < 0 || startY < 0 || startX > 15 || startY > 15) {
        throw std::runtime_error(
            "Initialzed soldier with x, y values out of scope");
    } else {
        pos_x_ = startX;
        pos_y_ = startY;
    }
}

Soldier::Soldier(const Soldier &other)
    : attack_(other.attack_),
      defense_(other.defense_),
      damage_(other.damage_),
      health_(other.health_),
      walk_distance_(other.walk_distance_),
      current_health_(other.current_health_),
      number_(other.number_),
      type_(other.type_),
      pos_x_(other.pos_x_),
      pos_y_(other.pos_y_) {}

void Soldier::receive_damage(int damage) {
    int division = damage / health_;
    int remainder = damage % health_;
    if (current_health_ - remainder <= 0) {
        number_ -= 1;
        current_health_ = health_ + current_health_ - remainder;
    } else {
        current_health_ -= remainder;
    }
    number_ -= division;
    if (number_ <= 0) {
        number_ = 0;
        current_health_ = 0;
    }
}

int Soldier::attack(int x, int y) {
    if (try_to_move(x, y)) {
        return damage_ * number_;
    }
    return 0;
}

bool Soldier::try_to_move(int x, int y) {
    if (std::abs(x - pos_x_) + std::abs(y - pos_y_) > walk_distance_) {
        return false;
    } else {
        pos_x_ = x;
        pos_y_ = y;
        return true;
    }
}

int Soldier::get_number() { return number_; }

int Soldier::getWalk() { return walk_distance_; }

bool Soldier::isAlive() {
    if (number_ > 0) {
        return true;
    } else {
        return false;
    }
}
int Soldier::getCurrentHealth() { return current_health_; }
int Soldier::getDamage() { return damage_; }
int Soldier::getHealth() { return health_; }

int Soldier::getX() { return pos_x_; }
int Soldier::getY() { return pos_y_; }

void Soldier::setCurrentHealth(int health) { current_health_ = health; }
void Soldier::setNumber(int num) { number_ = num; }
void Soldier::setX(int x) { pos_x_ = x; }
void Soldier::setY(int y) { pos_y_ = y; }

ArmyBranch Soldier::get_type() const { return type_; }