#include "Soldier.h"

Soldier::Soldier(int attack, int defense, int damage, int health,
                 int walk_distance, int number, int startX, int startY)
    : attack_(attack),
      defense_(defense),
      damage_(damage),
      health_(health),
      walk_distance_(walk_distance),
      current_health_(health),
      number_(number),
      pos_x_(startX),
      pos_y_(startY) {}

void Soldier::receive_damage(int damage) {
    int division = damage / health_;
    int remainder = damage % health_;
    if (current_health_ - remainder <= 0) {
        number_ -= 1;
        current_health_ = 5 + (current_health_ - remainder);
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
    for (int a = -1; a < 2; ++a) {
        for (int b = -1; b < 2; ++b) {
            if (try_to_move(x + b, y + a)) {
                return damage_ * number_;
            }
        }
    }
    return 0;
}

bool Soldier::try_to_move(int x, int y) {
    if (x < 1 || y < 1 || x > 16 || y > 16) {
        return false;
    }
    if (std::abs(pos_x_ - x) + std::abs(pos_y_ - y) > walk_distance_) {
        return false;
    } else {
        pos_x_ = x;
        pos_y_ = y;
        return true;
    }
}

int Soldier::get_number() { return number_; }

bool Soldier::isAlive() {
    if (number_ > 0) {
        return true;
    } else {
        return false;
    }
}

int Soldier::getX() { return pos_x_; }
int Soldier::getY() { return pos_y_; }