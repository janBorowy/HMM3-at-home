#include "MapField.h"

MapField::MapField() : val_(0) {}
MapField::MapField(int val, bool movable) : val_(val), movable_(movable) {}