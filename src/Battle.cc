#include "Battle.h"
#include <memory>
#include <stdexcept>
#include "HeroResources.h"

Battle::Battle(bool ai_game) : state_(heroTurn), counter_(0) {
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
        switch (i.unit) {
            case Archer:
                hero_army_.push_back(
                    std::make_unique<SType::Archer>(i.number, 0, pos));
                break;
            case Pikeman:
                hero_army_.push_back(
                    std::make_unique<SType::Pikeman>(i.number, 0, pos));
                break;
            case SwordsMan:
                hero_army_.push_back(
                    std::make_unique<SType::SwordsMan>(i.number, 0, pos));
                break;
        }
        pos += h_distribution;
    }

    id_num = 0;
    pos = (ROWS - 1 - e_distribution * (enemy_units.size() - 1)) / 2;

    for (auto i : enemy_units) {
        --id_num;
        switch (i.unit) {
            case Archer:
                enemy_army_.push_back(
                    std::make_unique<SType::Archer>(i.number, COLS - 1, pos));
                break;
            case Pikeman:
                enemy_army_.push_back(
                    std::make_unique<SType::Pikeman>(i.number, COLS - 1, pos));
                break;
            case SwordsMan:
                enemy_army_.push_back(std::make_unique<SType::SwordsMan>(
                    i.number, COLS - 1, pos));
                break;
        }
        pos += e_distribution;
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
        state_ = enemyTurn;
        setEnemyCounter(0);
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
