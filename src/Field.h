#pragma once

#include "GameEntity.h"

class Field : public GameEntity {
   public:
    Field();
    Field(unsigned short initX, unsigned short initY, unsigned short width,
          unsigned short height);
};