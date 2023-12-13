#pragma once
#include "MapObject.h"

class MapField {
   public:
    enum Type { EMPTY, WALL };

   private:
    Type type_;

   public:
    MapField();
    MapField(MapObject object, Type type);
    MapObject object_;
    bool movable() const;
};