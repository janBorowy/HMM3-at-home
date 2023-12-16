#pragma once
#include <stdexcept>
#include <vector>
#include "MapField.h"
#include "typedefs.h"

class GameMapException : std::runtime_error {
   public:
    GameMapException(std::string msg) : std::runtime_error(msg) {}
};

using Fields = std::vector<std::vector<MapField>>;
class GameMap {
    unsigned short width_;
    unsigned short height_;
    Fields fields_;

    void checkInBounds(int col, int row) const;

   public:
    GameMap(unsigned short width, unsigned short height);
    const Fields &fields() const;
    const MapField &at(int col, int row) const;
    const MapField &at(const Position &pos) const;
    MapField &at(int col, int row);
    void placeObject(int col, int row, const MapObject &object);
    unsigned short width() const;
    unsigned short height() const;
    bool fieldExists(int col, int row) const;
};