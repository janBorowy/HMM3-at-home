#pragma once
#include <cmath>

class Soldier {
   protected:
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
    Soldier(int attack, int defense, int damage, int health, int walk_distance,
            int number, int startX, int startY);
    void receive_damage(int damage);
    virtual int attack(int x, int y);
    bool try_to_move(int x, int y);
    int get_number();
    bool isAlive();
    int getX();
    int getY();
};