#include "MapParser.h"
#include <fstream>

MapParser::MapParser(unsigned short width, unsigned short height)
    : width_(width),
      height_(height),
      map_(width, height),
      elements_{{"0", MapObject::Type::NONE},
                {"g", MapObject::Type::GOLD},
                {"w", MapObject::Type::WOOD},
                {"o", MapObject::Type::ORE},
                {"t", MapObject::Type::TROGLODYTE}} {}

GameMap MapParser::parse(std::istream &data) {
    for (int row = 1; row <= height_; ++row) {
        for (int col = 1; col <= width_; ++col) {
            std::string str;
            data >> str;
            map_.at(col, row) = parseString(str);
        }
    }
    return map_;
}

MapField MapParser::parseString(const std::string &str) const {
    std::string identifier;
    auto it = str.begin();
    for (; it != str.end() && *it != '('; ++it) {
        identifier += *it;
    }
    if (identifier == "W") {
        return MapField(MapObject(MapObject::Type::NONE, 0),
                        MapField::Type::WALL);
    }
    MapObject::Type type;
    try {
        type = elements_.at(identifier);
    } catch (const std::out_of_range &e) {
        throw MapParserException("Illegal identifier");
    }
    if (identifier == "0") return MapField(MapObject(type, 0), MapField::EMPTY);
    std::string valueStr;
    for (++it; it != str.end() && *it != ')'; ++it) {
        valueStr += *it;
    }
    auto value = std::stoi(valueStr);
    return MapField(MapObject(type, value), MapField::EMPTY);
}