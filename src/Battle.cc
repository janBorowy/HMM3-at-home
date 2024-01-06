#include "Battle.h"
#include <memory>
#include <stdexcept>
#include "HeroResources.h"
#include "Soldier.h"
#include "SoldierTypes.h"

Battle::Battle(bool ai_game)
    : state_(heroTurn),
      counter_(0),
      ai_enemy_(ai_game),
      soldier_info_itr_(0),
      if_hero_soldier_info_(true) {
    hero_ = std::make_unique<AlivePlayer>();
    if (ai_game) {
        enemy_ = std::make_unique<AiPlayer>();
    } else {
        enemy_ = std::make_unique<AlivePlayer>();
    }
}

void Battle::setArmy(std::vector<UnitInfo> &hero_units,
                     std::vector<UnitInfo> &enemy_units) {
    hero_paw_nr_ = hero_units.size();
    enemy_paw_nr_ = enemy_units.size();

    int h_distribution = ROWS / hero_units.size();
    int e_distribution = ROWS / enemy_units.size();
    int pos = (ROWS - 1 - h_distribution * (hero_units.size() - 1)) / 2;

    int id_num = 0;
    for (auto i : hero_units) {
        ++id_num;
        pushToArmyVector(hero_army_, i.unit, i.number, 0, pos);
        pos += h_distribution;
    }

    id_num = 0;
    pos = (ROWS - 1 - e_distribution * (enemy_units.size() - 1)) / 2;

    for (auto i : enemy_units) {
        --id_num;
        pushToArmyVector(enemy_army_, i.unit, i.number, COLS - 1, pos);
        pos += e_distribution;
    }
}

void Battle::pushToArmyVector(std::vector<SoldierPtr> &vec, ArmyBranch type,
                              int num, int x, int y) {
    switch (type) {
        case ARCHER:
            vec.push_back(std::make_unique<SType::Archer>(num, x, y));
            break;
        case PIKEMAN:
            vec.push_back(std::make_unique<SType::Pikeman>(num, x, y));
            break;
        case SWORDSMAN:
            vec.push_back(std::make_unique<SType::SwordsMan>(num, x, y));
            break;
        case TROGLODYTE:
            vec.push_back(std::make_unique<SType::Troglodyte>(num, x, y));
            break;
        case MINOTAUR:
            vec.push_back(std::make_unique<SType::Minotaur>(num, x, y));
            break;
        case BEHOLDER:
            vec.push_back(std::make_unique<SType::Beholder>(num, x, y));
            break;
    }
}

void Battle::loadArmySprites() {
    for (auto &i : hero_army_) {
        i->loadSprites();
    }
    for (auto &i : enemy_army_) {
        i->loadSprites();
    }
}

void Battle::battleSpin(int x, int y) {
    switch (state_) {
        case heroTurn:
            if (hero_->makeMove(x, y, hero_army_, enemy_army_, counter_)) {
                updateState();
            }
            break;
        case enemyTurn:
            if (enemy_->makeMove(x, y, enemy_army_, hero_army_, counter_)) {
                updateState();
            }
            break;
        case waitForNextTurn:
            break;
        case won:
            std::cout << "hero won";
            break;
        case lost:
            std::cout << "hero lost";
            break;
    }
}

void Battle::updateState() {
    int h_count = 0;
    int e_count = 0;
    for (auto &i : hero_army_) {
        if (i->isAlive()) {
            ++h_count;
        }
    }
    for (auto &i : enemy_army_) {
        if (i->isAlive()) {
            ++e_count;
        }
    }
    if (e_count == 0 && h_count == 0) {
        throw std::runtime_error("Everyone is dead apparently.");
    } else if (e_count == 0) {
        state_ = won;
    } else if (h_count == 0) {
        state_ = lost;
    } else if (state_ == heroTurn) {
        if (setHeroCounter(counter_ + 1)) {
            return;
        }
        if (ai_enemy_) {
            state_ = waitForNextTurn;
        } else {
            state_ = enemyTurn;
            setEnemyCounter(0);
        }
        return;
    } else if (state_ == enemyTurn) {
        if (setEnemyCounter(counter_ + 1)) {
            return;
        }
        state_ = heroTurn;
        setHeroCounter(0);
        return;
    }
}

void Battle::handleNextTurn() {
    if ((state_ == heroTurn && ai_enemy_) || state_ == waitForNextTurn) {
        state_ = enemyTurn;
        setEnemyCounter(0);
        for (int i = 0; i < enemy_army_.size(); ++i) {
            battleSpin(0, 0);
            if (state_ == heroTurn) {
                break;
            }
        }
        setHeroCounter(0);
    } else if (state_ == heroTurn) {
        state_ = enemyTurn;
        setEnemyCounter(0);
    } else if (state_ == enemyTurn) {
        state_ = heroTurn;
        setHeroCounter(0);
    }
}

bool Battle::setHeroCounter(int counter) {
    for (int i = counter; i < hero_army_.size(); ++i) {
        if (hero_army_.at(i)->isAlive()) {
            counter_ = i;
            return true;
        }
    }
    return false;
}
bool Battle::setEnemyCounter(int counter) {
    for (int i = counter; i < enemy_army_.size(); ++i) {
        if (enemy_army_.at(i)->isAlive()) {
            counter_ = i;
            return true;
        }
    }
    return false;
}

BattleState Battle::getState() { return state_; }
std::vector<SoldierPtr> &Battle::getHeroArmy() { return hero_army_; }
std::vector<SoldierPtr> &Battle::getEnemyArmy() { return enemy_army_; }
int Battle::getCounter() { return counter_; }

bool Battle::setSoldierInfo(int x, int y) {
    for (int i = 0; i < hero_army_.size(); ++i) {
        if (hero_army_.at(i)->getX() == x && hero_army_.at(i)->getY() == y) {
            soldier_info_itr_ = i;
            if_hero_soldier_info_ = true;
            return true;
        }
    }
    for (int i = 0; i < enemy_army_.size(); ++i) {
        if (enemy_army_.at(i)->getX() == x && enemy_army_.at(i)->getY() == y) {
            soldier_info_itr_ = i;
            if_hero_soldier_info_ = false;
            return true;
        }
    }
    return false;
}

SoldierPtr &Battle::getSoldierForInfo() {
    if (if_hero_soldier_info_) {
        return hero_army_.at(soldier_info_itr_);
    } else {
        return enemy_army_.at(soldier_info_itr_);
    }
}