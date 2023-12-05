#include "MapObject.h"

MapObject::MapObject(Type type, int value) : type_(type), value_(value) {}
MapObject::Type MapObject::type() const { return type_; }
int MapObject::value() const { return value_; }