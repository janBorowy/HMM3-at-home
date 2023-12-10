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
        Node(int priority, Position const &pos)
            : priority_(priority), pos_(pos) {}
        friend bool operator<(Node const &l, Node const &r) {
            return l.priority_ < r.priority_;
        }
        friend bool operator>(Node const &l, Node const &r) { return r < l; }
    };

   public:
    ShortestPathFinder(Position const &src, Position const &dest);
    void virtual visit(GameMap const &map);
    std::vector<Position> result() const;
    double euclideanLength(Position const &src, Position const &dest);
};