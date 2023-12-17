#include <stdexcept>
#include "Soldier.h"

Soldier::Soldier(int attack, int defense, int damage, int health,
                 int walk_distance, int number, int startX, int startY)
    : attack_(attack),
      defense_(defense),
      damage_(damage),
      health_(health),
      walk_distance_(walk_distance),
      current_health_(health),
      number_(number)

{
    if (startX < 0 || startY < 0 || startX > SIZE-1 || startY > SIZE-1) {
        throw std::runtime_error(
            "Initialzed soldier with x, y values out of scope");
    } else {
        pos_x_ = startX;
        pos_y_ = startY;
    }
}

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

bool Soldier::isAlive() {
    if (number_ > 0) {
        return true;
    } else {
        return false;
    }
}

int Soldier::getX() { return pos_x_; }
int Soldier::getY() { return pos_y_; }