#include <vector>
#include "GameMapVisitator.h"
#include "typedefs.h"

class ShortestPathFinder : public GameMapVisitator {
    Position src_;
    Position dest_;
    std::vector<Position> result_;

    struct Node {
        int priority_;
        Position pos_;
        Node(int priority, const Position &pos)
            : priority_(priority), pos_(pos) {}
        friend bool operator<(const Node &l, const Node &r) {
            return l.priority_ < r.priority_;
        }
        friend bool operator>(const Node &l, const Node &r) { return r < l; }
    };

   public:
    ShortestPathFinder(const Position &src, const Position &dest);
    void virtual visit(const GameMap &map);
    std::vector<Position> result() const;
    double euclideanLength(const Position &src, const Position &dest);
};