#include "Battle.h"
#include "HeroResources.h"
#include "SoldierTypes.h"

Battle::Battle(std::vector<UnitInfo> &hero_units,
               std::vector<UnitInfo> &enemy_units)
    : state_(heroTurn), paw_counter_(0) {
    clear_grid();

    int h_distribution = Rows / hero_units.size();
    int e_distribution = Rows / enemy_units.size();
    int pos = (Rows - 1 - h_distribution * (hero_units.size() - 1)) / 2;

    int id_num = 0;
    for (auto i : hero_units) {
        ++id_num;
        switch (i.unit) {
            case Archer:
                hero_.emplace(id_num, new SType::Archer(i.number, 0, pos));
                break;
            case Pikeman:
                hero_.emplace(id_num, new SType::Pikeman(i.number, 0, pos));
                break;
            case SwordsMan:
                hero_.emplace(id_num, new SType::SwordsMan(i.number, 0, pos));
                break;
        }
        game_grid[pos][0] = id_num;
        hero_keys_.push_back(id_num);
        pos += h_distribution;
    }

    id_num = 0;
    pos = (Rows - 1 - e_distribution * (enemy_units.size() - 1)) / 2;

    for (auto i : enemy_units) {
        --id_num;
        switch (i.unit) {
            case Archer:
                enemy_.emplace(id_num,
                               new SType::Archer(i.number, Cols - 1, pos));
                break;
            case Pikeman:
                enemy_.emplace(id_num,
                               new SType::Pikeman(i.number, Cols - 1, pos));
                break;
            case SwordsMan:
                enemy_.emplace(id_num,
                               new SType::SwordsMan(i.number, Cols - 1, pos));
                break;
        }
        game_grid[pos][Cols - 1] = id_num;
        enemy_keys_.push_back(id_num);
        pos += e_distribution;
    }
}

void Battle::battle_spin(int x, int y) {
    switch (state_) {
        case heroTurn:
            if (game_grid[y][x] < 0) {
                int damage = hero_[hero_keys_.at(paw_counter_)]->attack(x, y);
                if (damage > 0) {
                    ++paw_counter_;
                    enemy_[game_grid[y][x]]->receive_damage(damage);
                    update_grid();
                }
            } else if (game_grid[y][x] == 0) {
                if (hero_[hero_keys_.at(paw_counter_)]->try_to_move(x, y)) {
                    ++paw_counter_;
                    update_grid();
                }
            } else {
                std::cout << "Do you want to kill yourself or your comrades?!!";
            }

            if (paw_counter_ >= hero_keys_.size()) {
                state_ = enemyTurn;
                paw_counter_ = 0;
            }
            break;
        case enemyTurn:
            if (game_grid[y][x] > 0) {
                int damage = enemy_[enemy_keys_.at(paw_counter_)]->attack(x, y);
                if (damage > 0) {
                    ++paw_counter_;
                    hero_[game_grid[y][x]]->receive_damage(damage);
                    update_grid();
                }
            } else if (game_grid[y][x] == 0) {
                if (enemy_[enemy_keys_.at(paw_counter_)]->try_to_move(x, y)) {
                    ++paw_counter_;
                    update_grid();
                }
            } else {
                std::cout << "Do you want to kill yourself or your comrades?!!";
            }

            if (paw_counter_ >= enemy_keys_.size()) {
                state_ = heroTurn;
                paw_counter_ = 0;
            }
            break;
        case won:
            std::cout << "hero won";
            break;
        case lost:
            std::cout << "hero lost";
            break;
    }
}

void Battle::clear_grid() {
    for (int i = 0; i < Rows; ++i) {
        for (int j = 0; j < Cols; ++j) {
            game_grid[i][j] = 0;
        }
    }
}

void Battle::update_grid() {
    clear_grid();
    int countHero = 0;
    int countEnemy = 0;
    for (auto &pair : enemy_) {
        if (pair.second->get_number() > 0) {
            game_grid[pair.second->getY()][pair.second->getX()] = pair.first;
            ++countEnemy;
        }
    }
    for (auto &pair : hero_) {
        if (pair.second->get_number() > 0) {
            game_grid[pair.second->getY()][pair.second->getX()] = pair.first;
            ++countHero;
        }
    }
    if (countEnemy == 0) {
        state_ = won;
    }
    if (countHero == 0) {
        state_ = lost;
    }
}

void Battle::print_grid() {
    int counterX = 0;
    int counterY = 0;
    for (int i = -1; i < Rows; ++i) {
        for (int j = -1; j < Cols; ++j) {
            if (i == -1 && j != -1) {
                if (counterX == 0) {
                    std::cout << "    " << counterX;
                } else if (counterX < 10) {
                    std::cout << "  " << counterX;
                } else {
                    std::cout << " " << counterX;
                }

                ++counterX;
            } else if (j == -1 && i != -1) {
                if (counterY < 10) {
                    std::cout << " " << counterY;
                } else {
                    std::cout << counterY;
                }
                ++counterY;
            } else if (i != -1 && j != -1) {
                if (game_grid[i][j] < 0) {
                    std::cout << " " << game_grid[i][j];
                } else {
                    std::cout << "  " << game_grid[i][j];
                }
            }
        }
        std::cout << "\n";
    }
}
