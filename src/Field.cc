#include "Field.h"

Field::Field() : GameEntity("empty_field.png", 0, 0, 0, 0) {}

Field::Field(unsigned short initX, unsigned short initY, unsigned short width,
             unsigned short height)
    : GameEntity("empty_field.png", initX, initY, width, height) {}