#pragma once

#include <array>
#include <memory>
#include <utility>
#include "GameEntity.h"
#include "GameMap.h"
#include "MapVisitator.h"
#include "Renderer.h"
#include "typedefs.h"

constexpr int GRID_WIDTH = 20;
constexpr int GRID_HEIGHT = 20;

class MapExtrinsic {
    unsigned short x_;
    unsigned short y_;
    unsigned short width_;
    unsigned short height_;
    unsigned short fieldHeight_;
    unsigned short fieldWidth_;
    GameMap map_;
    SpriteUPtr fieldSprite_;
    SpriteUPtr wallSprite_;
    SpriteUPtr goldFieldSprite_;
    SpriteUPtr oreFieldSprite_;
    SpriteUPtr woodFieldSprite_;
    SpriteUPtr enemyFieldSprite_;
    Position cameraLeftUpperCorner_;
    void loadMapSprites();
    void drawField(int x, int y, MapField::Type type,
                   const Renderer &renderer) const;
    void drawFieldObject(int x, int y, MapObject::Type type,
                         const Renderer &renderer) const;
    std::vector<Position> movementIndicators_;

   public:
    MapExtrinsic(unsigned short initX, unsigned short initY,
                 unsigned short width, unsigned short height,
                 const GameMap &map);
    void draw(const Renderer &renderer) const;
    void moveCameraBy(Position delta);
    Position getCameraPosition() const;
    const MapField &at(int row, int col);
    int x() const;
    int y() const;
    int fieldWidth() const;
    int fieldHeight() const;
    void accept(MapVisitator *visitator);
    GameMap &gameMap();
};