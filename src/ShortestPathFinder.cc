#include <algorithm>
#include <cmath>
#include <limits>
#include "ShortestPathFinder.h"

namespace {
inline double squareOf(double x) { return x * x; }
}  // namespace

ShortestPathFinder::ShortestPathFinder(Position const &src,
                                       Position const &dest)
    : src_(src), dest_(dest), result_{} {}

double ShortestPathFinder::euclideanLength(Position const &src,
                                           Position const &dest) {
    return sqrt(squareOf(dest.first - src.first) +
                squareOf(dest.second - src.second));
}

void ShortestPathFinder::visit(GameMap const &map) {
    std::vector<Node> toCheck;

    std::vector<std::vector<Position>> previous =
        std::vector<std::vector<Position>>(map.height(),
                                           std::vector<Position>(map.width()));

    std::vector<std::vector<int>> distance = std::vector<std::vector<int>>(
        map.height(),
        std::vector<int>(map.width(), std::numeric_limits<int>::max()));

    std::vector<std::vector<double>> predicted =
        std::vector<std::vector<double>>(
            map.height(), std::vector<double>(
                              map.width(), std::numeric_limits<double>::max()));

    distance[src_.second][src_.first] = 0;
    predicted[src_.second][src_.first] = euclideanLength(src_, dest_);

    toCheck.push_back(Node(predicted[src_.second][src_.first], src_));
    std::push_heap(toCheck.begin(), toCheck.end());
}
std::vector<Position> ShortestPathFinder::result() const { return result_; }
