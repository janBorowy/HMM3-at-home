#pragma once
#include <climits>
#include <iostream>
#include <vector>
#include "Player.h"
#include "SoldierTypes.h"
constexpr int DEPTH = 2;

struct State {
    std::vector<SoldierPtr> my_army;
    std::vector<SoldierPtr> enemy_army;
    State() = default;
    State(const std::vector<SoldierPtr> &my_vec,
          const std::vector<SoldierPtr> &enemy_vec);
    State(const State &other);
};

class AiPlayer : public Player {
    int paw_nr_;
    State player_move_;

   public:
    virtual bool makeMove(int x, int y, std::vector<SoldierPtr> &my_army,
                          std::vector<SoldierPtr> &enemy_army, int paw_nr);

    int minimax(const State &position, int depth, int alpha, int beta,
                bool maximizingPlayer, bool beginning);

    void cloneState(const State &state, State &new_state);
    bool isGameOver(const State &position) const;
    int evaluatePosition(const State &position) const;
    void generateChildren(const State &position, std::vector<State> &children,
                          bool if_max_player);
    void addChildren(std::vector<State> &children, const State &state,
                     int nesting_level, int max_level, bool if_max_player);
};