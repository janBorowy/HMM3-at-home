#include <iostream>
#include <map>
#include <stdexcept>
#include <string>
#include "GameMap.h"

using MapElements = std::map<std::string, MapObject::Type>;

class MapParserException : std::runtime_error {
   public:
    MapParserException(std::string msg) : std::runtime_error(msg) {}
};

class MapParser {
    unsigned short width_;
    unsigned short height_;
    GameMap map_;
    MapElements elements_;
    MapField parseString(std::string const &str) const;

   public:
    MapParser(unsigned short width, unsigned short height);
    GameMap parse(std::istream &data);
};