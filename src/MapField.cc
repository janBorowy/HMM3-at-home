#include "GameData.h"
#include "MapField.h"

MapField::MapField()
    : type_(EMPTY), object_(MapObject(MapObject::Type::NONE, 0)) {}
MapField::MapField(MapObject object, MapField::Type type)
    : object_(object), type_(type) {}
bool MapField::movable() const {
    switch (type_) {
        case EMPTY:
            return true;
        case WALL:
            return false;
    }
    return true;
}