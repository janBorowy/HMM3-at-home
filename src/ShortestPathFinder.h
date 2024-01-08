#pragma once
#include <queue>
#include <vector>
#include "GameMapVisitator.h"
#include "stdexcept"
#include "typedefs.h"

class ShortestPathFinderException : public std::runtime_error {
   public:
    ShortestPathFinderException(std::string message)
        : std::runtime_error(message) {}
};

class ShortestPathFinder : public GameMapVisitator {
    Position src_;
    Position dest_;
    std::vector<Position> result_;

    struct Node {
        Position pos_;
        double distanceFromDest_;
        bool operator>(const Node &rhs) const;
        bool operator<(const Node &rhs) const;
        Node(const Position &position, double distanceFromDest_);
    };

   public:
    ShortestPathFinder(const Position &src, const Position &dest);
    void virtual visit(const GameMap &map);
    std::vector<Position> result() const;
    double euclideanLength(const Position &src, const Position &dest);
    void updateQueue(std::priority_queue<Node> &queue, const Position &pos,
                     double priority);
};