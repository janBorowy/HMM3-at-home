#include <cmath>
#include <iostream>
#include <stdexcept>
#include "AlivePlayer.h"

bool AlivePlayer::makeMove(int x, int y, std::vector<SoldierPtr> &my_army,
                           std::vector<SoldierPtr> &enemy_army, int paw_nr) {
    my_x_ = my_army.at(paw_nr)->getX();
    my_y_ = my_army.at(paw_nr)->getY();

    bool attack = false;

    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            game_grid[i][j] = 0;
        }
    }
    for (auto &i : my_army) {
        game_grid[i->getY()][i->getX()] = 1;
        if (i->getX() == x && i->getY() == y) {
            std::cout << "Do you want to kill yourself or your comrades!!?";
            return false;
        }
    }
    int enemy_counter = 0;
    int enemy_itr = 0;
    for (auto &i : enemy_army) {
        game_grid[i->getY()][i->getX()] = -1;

        if (i->getX() == x && i->getY() == y && i->isAlive()) {
            attack = true;
            enemy_itr = enemy_counter;
        }
        ++enemy_counter;
    }
    if (attack) {
        std::pair<int, int> x_y_to_go = calculateRoute(x, y);
        int damage =
            my_army.at(paw_nr)->attack(x_y_to_go.first, x_y_to_go.second);
        if (damage == 0) {
            return false;
        }
        enemy_army.at(enemy_itr)->receive_damage(damage);
        return true;
    }
    return my_army.at(paw_nr)->try_to_move(x, y);
}

std::pair<int, int> AlivePlayer::calculateRoute(int x, int y) {
    int route = 100;

    int possible_x = 100;
    int possible_y = 100;
    for (int a = -1; a < 2; ++a) {
        for (int b = -1; b < 2; ++b) {
            if (y + b < 0 || x + a < 0 || y + b > 15 || x + a > 15) {
                continue;
            }
            if (game_grid[y + b][x + a] != 0) {
                continue;
            }
            int new_route = std::abs(x + a - my_x_) + std::abs(y + b - my_y_);
            if (new_route < route) {
                route = new_route;
                possible_x = x + a;
                possible_y = y + b;
            }
        }
    }
    return std::make_pair(possible_x, possible_y);
}