#include "MapField.h"
#include "GameData.h"

MapField::MapField()
    : type_(EMPTY), object_(MapObject(MapObject::Type::NONE, 0)) {}
MapField::MapField(MapObject object, MapField::Type type)
    : object_(object), type_(type) {}
bool MapField::movable(bool isFinalDestination) const {
    switch (type_) {
        case EMPTY:
            if (object_.type() == MapObject::Type::ENEMY) {
                return isFinalDestination;
            }
            return true;
        case WALL:
            return false;
    }
    return true;
}
MapField::Type MapField::type() const { return type_; }