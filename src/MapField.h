#pragma once
#include "MapObject.h"
class MapField {
    bool movable_;

   public:
    MapField();
    MapField(MapObject object, bool movable_);
    MapObject object_;
};