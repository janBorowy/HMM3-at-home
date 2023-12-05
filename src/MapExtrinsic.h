#pragma once

#include <array>
#include "GameEntity.h"
#include "GameMap.h"
#include "Renderer.h"

constexpr int GRID_WIDTH = 16;
constexpr int GRID_HEIGHT = 16;

class MapExtrinsic {
    unsigned short x_;
    unsigned short y_;
    unsigned short width_;
    unsigned short height_;
    unsigned short fieldHeight_;
    unsigned short fieldWidth_;
    unsigned short selectedRow_;
    unsigned short selectedCol_;
    GameMap map_;
    SpriteUPtr fieldSprite_;
    SpriteUPtr goldFieldSprite_;

   public:
    MapExtrinsic(unsigned short initX, unsigned short initY,
                 unsigned short width, unsigned short height);
    void drawFields(Renderer const &renderer) const;
    void drawFieldTypeSpecific(int x, int y, MapObject::Type type,
                               Renderer const &renderer) const;
    void handleClick(int x, int y);
    MapField const &at(int row, int col);
};