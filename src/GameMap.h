#pragma once
#include <stdexcept>
#include <vector>
#include "MapField.h"

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
    Fields const &fields() const;
    MapField const &at(int col, int row) const;
    MapField &at(int col, int row);
    void placeObject(int col, int row, MapObject const &object);
    unsigned short width() const;
    unsigned short height() const;
    bool fieldExists(int col, int row) const;
};