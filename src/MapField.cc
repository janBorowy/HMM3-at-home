#include "GameData.h"
#include "MapField.h"

MapField::MapField() : object_(MapObject(MapObject::Type::NONE, 0)) {}
MapField::MapField(MapObject object, bool movable)
    : object_(object), movable_(movable) {}