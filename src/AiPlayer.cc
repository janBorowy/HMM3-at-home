#include "AiPlayer.h"
#include "AlivePlayer.h"

State::State(const State &other) {
    for (const auto &i : other.my_army) {
        my_army.push_back(i->clone());
    }
    for (const auto &i : other.enemy_army) {
        enemy_army.push_back(i->clone());
    }
}

State::State(const std::vector<SoldierPtr> &my_vec,
             const std::vector<SoldierPtr> &enemy_vec) {
    for (const auto &i : my_vec) {
        my_army.push_back(i->clone());
    }
    for (const auto &i : enemy_vec) {
        enemy_army.push_back(i->clone());
    }
}

bool AiPlayer::makeMove(int x, int y, std::vector<SoldierPtr> &my_army,
                        std::vector<SoldierPtr> &enemy_army, int paw_nr) {
    paw_nr_ = paw_nr;
    State base_state(my_army, enemy_army);
    // for (auto &i : my_army) {
    //     base_state.my_army.push_back(i->clone());
    // }
    // for (auto &i : enemy_army) {
    //     base_state.enemy_army.push_back(i->clone());
    // }
    minimax(base_state, DEPTH, INT_MIN, INT_MAX, true, true);

    for (int i = 0; i < my_army.size(); ++i) {
        my_army.at(i)->setCurrentHealth(
            player_move_.my_army.at(i)->getCurrentHealth());
        my_army.at(i)->setNumber(player_move_.my_army.at(i)->get_number());
        my_army.at(i)->setX(player_move_.my_army.at(i)->getX());
        my_army.at(i)->setY(player_move_.my_army.at(i)->getY());
    }
    for (int i = 0; i < enemy_army.size(); ++i) {
        enemy_army.at(i)->setCurrentHealth(
            player_move_.enemy_army.at(i)->getCurrentHealth());
        enemy_army.at(i)->setNumber(
            player_move_.enemy_army.at(i)->get_number());
    }
    return true;
}

int AiPlayer::minimax(const State &position, int depth, int alpha, int beta,
                      bool maximizingPlayer, bool beginning) {
    if (depth == 0 || isGameOver(position)) {
        return evaluatePosition(position);
    }
    std::vector<State> children;
    if (maximizingPlayer) {
        int maxEval = INT_MIN;
        generateChildren(position, children, true);
        if (beginning) {
            for (const auto &child : children) {
                int eval = minimax(child, depth - 1, alpha, beta, false, false);
                if (eval > maxEval) {
                    cloneState(child, player_move_);
                    maxEval = eval;
                }
                // maxEval = std::max(maxEval, eval);
                alpha = std::max(alpha, eval);
                if (beta <= alpha) {
                    break;
                }
            }
        } else {
            for (const auto &child : children) {
                int eval = minimax(child, depth - 1, alpha, beta, false, false);
                maxEval = std::max(maxEval, eval);
                alpha = std::max(alpha, eval);
                if (beta <= alpha) {
                    break;
                }
            }
        }
        return maxEval;
    } else {
        generateChildren(position, children, false);
        int minEval = INT_MAX;
        for (const auto &child : children) {
            int eval = minimax(child, depth - 1, alpha, beta, true, false);
            minEval = std::min(minEval, eval);
            beta = std::min(beta, eval);
            if (beta <= alpha) {
                break;
            }
        }
        return minEval;
    }
}

void AiPlayer::cloneState(const State &state, State &new_state) {
    // State new_state;
    new_state.my_army.clear();
    new_state.enemy_army.clear();
    for (const auto &i : state.my_army) {
        new_state.my_army.push_back(i->clone());
    }
    for (const auto &i : state.enemy_army) {
        new_state.enemy_army.push_back(i->clone());
    }
    // return new_state;
}

bool AiPlayer::isGameOver(const State &position) const {
    int my_num = 0;
    int enemy_num = 0;
    for (auto &i : position.my_army) {
        my_num += i->get_number();
    }
    for (auto &i : position.enemy_army) {
        enemy_num += i->get_number();
    }
    if (my_num == 0 || enemy_num == 0) {
        return true;
    } else {
        return false;
    }
}

int AiPlayer::evaluatePosition(const State &position) const {
    // Implement your static evaluation function
    const float distance_attack_bonus = 1.2;
    int my_damage = 0;
    int my_health = 0;

    int enemy_damage = 0;
    int enemy_health = 0;

    for (auto &i : position.my_army) {
        my_health += i->get_number() * i->getHealth() -
                     (i->getHealth() - i->getCurrentHealth());
        if (i->get_type() == Soldier::ARCHER) {
            my_damage +=
                distance_attack_bonus * i->get_number() * i->getDamage();
        } else {
            my_damage += i->get_number() * i->getDamage();
        }
    }
    for (auto &i : position.enemy_army) {
        enemy_health += i->get_number() * i->getHealth() -
                        (i->getHealth() - i->getCurrentHealth());
        if (i->get_type() == Soldier::ARCHER) {
            enemy_damage +=
                distance_attack_bonus * i->get_number() * i->getDamage();
        } else {
            enemy_damage += i->get_number() * i->getDamage();
        }
    }

    return my_damage + my_health - enemy_health - enemy_damage;
}

void AiPlayer::generateChildren(const State &position,
                                std::vector<State> &children,
                                bool if_max_player) {
    // std::vector<State> children;
    children.clear();
    addChildren(children, position, 0, position.my_army.size(), if_max_player);
    // return children;
}

void AiPlayer::addChildren(std::vector<State> &children, const State &state,
                           int nesting_level, int max_level,
                           bool if_max_player) {
    State new_state;
    AlivePlayer alive_player;
    cloneState(state, new_state);
    if (if_max_player) {
        for (int i = 0; i < COLS; ++i) {
            for (int j = 0; j < ROWS; ++j) {
                if (alive_player.makeMove(i, j, new_state.my_army,
                                          new_state.enemy_army,
                                          nesting_level)) {
                    ++nesting_level;
                    if (nesting_level == max_level) {
                        children.push_back(new_state);
                    } else {
                        addChildren(children, new_state, nesting_level,
                                    max_level, true);
                    }
                    --nesting_level;
                    cloneState(state, new_state);
                }
            }
        }
        // std::cout << "bll";
    } else {
        for (int i = 0; i < COLS; ++i) {
            for (int j = 0; j < ROWS; ++j) {
                if (alive_player.makeMove(i, j, new_state.enemy_army,
                                          new_state.my_army, nesting_level)) {
                    ++nesting_level;
                    if (nesting_level == max_level) {
                        children.push_back(new_state);
                    } else {
                        addChildren(children, new_state, nesting_level,
                                    max_level, false);
                    }
                    --nesting_level;
                    cloneState(state, new_state);
                }
            }
        }
    }
}
