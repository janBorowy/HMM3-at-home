#include "ShortestPathFinder.h"
#include <algorithm>
#include <cmath>
#include <cstdint>
#include <limits>
#include <unordered_map>

namespace {
inline double squareOf(double x) { return x * x; }
}  // namespace

ShortestPathFinder::ShortestPathFinder(const Position &src,
                                       const Position &dest)
    : src_(src), dest_(dest), result_{} {}

double ShortestPathFinder::euclideanLength(const Position &src,
                                           const Position &dest) {
    return std::hypot(dest.first - src.first, dest.second - src.second);
}

template <typename T>
T &at(std::vector<std::vector<T>> &twoDimensionalVector, int x, int y) {
    return twoDimensionalVector[y - 1][x - 1];
}

template <typename T>
const T &at(const std::vector<std::vector<T>> &twoDimensionalVector, int x,
            int y) {
    return twoDimensionalVector[y - 1][x - 1];
}

template <typename T>
T &at(std::vector<std::vector<T>> &twoDimensionalVector, const Position &p) {
    return at(twoDimensionalVector, p.first, p.second);
}

template <typename T>
const T &at(const std::vector<std::vector<T>> &twoDimensionalVector,
            const Position &p) {
    return at(twoDimensionalVector, p.first, p.second);
}

bool ShortestPathFinder::Node::operator>(const Node &rhs) const {
    return distanceFromDest_ < rhs.distanceFromDest_;
}

bool ShortestPathFinder::Node::operator<(const Node &rhs) const {
    return distanceFromDest_ > rhs.distanceFromDest_;
}

ShortestPathFinder::Node::Node(const Position &position,
                               double distanceFromDest)
    : pos_{position}, distanceFromDest_{distanceFromDest} {}

std::vector<Position> ShortestPathFinder::getNeighbours(int width, int height,
                                                        const Position &pos,
                                                        const GameMap &map) {
    int x = pos.first;
    int y = pos.second;
    std::vector<Position> output;

    if (x > 1 && map.at(x - 1, y).movable(Position{x - 1, y} == dest_)) {
        output.push_back({x - 1, y});
    }
    if (x < width && map.at(x + 1, y).movable(Position{x + 1, y} == dest_)) {
        output.push_back({x + 1, y});
    }
    if (y > 1 && map.at(x, y - 1).movable(Position{x, y - 1} == dest_)) {
        output.push_back({x, y - 1});
    }
    if (y < height && map.at(x, y + 1).movable(Position{x, y + 1} == dest_)) {
        output.push_back({x, y + 1});
    }
    return output;
}

void ShortestPathFinder::updateQueue(std::priority_queue<Node> &queue,
                                     const Position &pos,
                                     double predictedDistance) {
    Node updated(pos, predictedDistance);
    std::vector<Node> popped;
    while (!queue.empty()) {
        auto current = queue.top();
        queue.pop();

        if (current.pos_ == pos) {
            if (current < updated) {
                current = updated;
            }
            popped.push_back(current);
            break;
        }
        popped.push_back(current);
    }
    queue.push(updated);
    for (const auto &elem : popped) {
        queue.push(elem);
    }
}

std::vector<Position> reconstructPath(
    const std::vector<std::vector<Position>> &previous, const Position &dest) {
    std::vector<Position> result = {dest};
    auto current = dest;
    while (at(previous, current) != Position{-1, -1}) {
        current = at(previous, current);
        result.push_back(current);
    }
    std::reverse(result.begin(), result.end());
    return result;
}

void ShortestPathFinder::visit(const GameMap &map) {
    int width = map.width();
    int height = map.height();

    std::priority_queue<Node> toCheck;

    std::vector<std::vector<Position>> previous(
        height, std::vector<Position>(width, {-1, -1}));
    std::vector<std::vector<int>> knownDistance(
        height, std::vector<int>(width, INT32_MAX));
    std::vector<std::vector<double>> predictedDistance(
        height, std::vector<double>(width, MAXFLOAT));

    at(knownDistance, src_) = 0;
    at(predictedDistance, src_) = euclideanLength(src_, dest_);

    toCheck.push(Node(src_, at(predictedDistance, src_)));
    while (!toCheck.empty()) {
        auto current = toCheck.top();
        toCheck.pop();
        if (current.pos_ == dest_) {
            result_ = reconstructPath(previous, dest_);
            return;
        }

        for (const auto &neighbour :
             getNeighbours(width, height, current.pos_, map)) {
            int realDistance = at(knownDistance, current.pos_) + 1;
            if (realDistance < at(knownDistance, neighbour)) {
                at(previous, neighbour) = current.pos_;
                at(knownDistance, neighbour) = realDistance;
                at(predictedDistance, neighbour) =
                    static_cast<double>(realDistance) +
                    euclideanLength(neighbour, dest_);
                updateQueue(toCheck, neighbour,
                            at(predictedDistance, neighbour));
            }
        }
    }
    throw ShortestPathFinderException("Path does not exist");
};

std::vector<Position> ShortestPathFinder::result() const { return result_; }
