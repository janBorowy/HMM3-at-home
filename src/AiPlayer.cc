#include "AiPlayer.h"
#include <algorithm>
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

    minimax(base_state, DEPTH, INT_MIN, INT_MAX, true, true, paw_nr);

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
                      bool maximizingPlayer, bool beginning, int paw_nr) {
    if (depth == 0 || isGameOver(position)) {
        return evaluatePosition(position);
    }

    State child;
    cloneState(position, child);
    int x = 0;
    int y = 0;
    if (maximizingPlayer) {
        int maxEval = INT_MIN;

        while (updateChild(child, true, paw_nr, x, y)) {
            int eval;
            eval = minimax(child, depth - 1, alpha, beta, false, false, 0);
            if (eval > maxEval) {
                if (beginning) {
                    cloneState(child, player_move_);
                }
                maxEval = eval;
            }

            alpha = std::max(alpha, eval);
            if (beta <= alpha) {
                break;
            }
            cloneState(position, child);
        }

        return maxEval;
    } else {
        int minEval = INT_MAX;

        while (updateChild(child, false, paw_nr, x, y)) {
            int eval;
            ++paw_nr;
            if (paw_nr >= position.enemy_army.size()) {
                eval = minimax(child, depth - 1, alpha, beta, true, false,
                               paw_nr_);
            } else {
                eval = minimax(child, depth - 1, alpha, beta, false, false,
                               paw_nr);
            }
            minEval = std::min(minEval, eval);
            beta = std::min(beta, eval);
            if (beta <= alpha) {
                break;
            }
            --paw_nr;
            cloneState(position, child);
        }
        return minEval;
    }
}

void AiPlayer::cloneState(const State &state, State &new_state) {
    new_state.my_army.clear();
    new_state.enemy_army.clear();
    std::transform(state.my_army.begin(), state.my_army.end(),
                   std::back_inserter(new_state.my_army),
                   [](const auto &i) { return i->clone(); });

    std::transform(state.enemy_army.begin(), state.enemy_army.end(),
                   std::back_inserter(new_state.enemy_army),
                   [](const auto &i) { return i->clone(); });
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
    int enemy_health = 0;

    int distance = 0;

    for (auto &i : position.enemy_army) {
        enemy_health += i->get_number() * i->getHealth() -
                        (i->getHealth() - i->getCurrentHealth());
        for (auto &j : position.my_army) {
            if (i->isAlive() && j->isAlive()) {
                distance += std::pow(i->getX() - j->getX(), 2) +
                            std::pow(i->getY() - j->getY(), 2);
            }
        }
    }

    return -enemy_health - distance / 70;
}

bool AiPlayer::updateChild(State &child, bool if_max_player, int paw_nr, int &x,
                           int &y) {
    AlivePlayer alive_player;

    if (if_max_player) {
        for (int i = x; i < COLS; ++i) {
            for (int j = y; j < ROWS; ++j) {
                if (alive_player.makeMove(i, j, child.my_army, child.enemy_army,
                                          paw_nr)) {
                    x = i;
                    y = j;
                    ++y;
                    if (y == ROWS) {
                        y = 0;
                        ++x;
                        if (x == COLS) {
                            return false;
                        }
                    }
                    return true;
                }
            }
            if (i == COLS - 1) {
                return false;
            }
            y = 0;
        }
    } else {
        for (int i = x; i < COLS; ++i) {
            for (int j = y; j < ROWS; ++j) {
                if (alive_player.makeMove(i, j, child.enemy_army, child.my_army,
                                          paw_nr)) {
                    x = i;
                    y = j;
                    ++y;
                    if (y == ROWS) {
                        y = 0;
                        ++x;
                        if (x == COLS) {
                            return false;
                        }
                    }
                    return true;
                }
            }
            if (i == COLS - 1) {
                return false;
            }
            y = 0;
        }
    }
    return true;
}
