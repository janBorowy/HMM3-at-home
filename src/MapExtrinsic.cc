#include <algorithm>
#include "GameData.h"
#include "MapExtrinsic.h"

MapExtrinsic::MapExtrinsic(unsigned short initX, unsigned short initY,
                           unsigned short width, unsigned short height,
                           GameMap const &map)
    : x_{initX},
      y_{initY},
      fieldHeight_(height / GRID_HEIGHT),
      fieldWidth_(width / GRID_WIDTH),
      map_{map},
      cameraLeftUpperCorner_{0, 0} {
    loadMapSprites();
}

void MapExtrinsic::drawFields(Renderer const &renderer) const {
    for (int row = cameraLeftUpperCorner_.second;
         row < 16 + cameraLeftUpperCorner_.second; ++row) {
        for (int col = cameraLeftUpperCorner_.first;
             col < 16 + cameraLeftUpperCorner_.first; ++col) {
            auto &field = map_.fields()[row][col];
            int drawX = x_ + (col - cameraLeftUpperCorner_.first) * fieldWidth_;
            int drawY =
                y_ + (row - cameraLeftUpperCorner_.second) * fieldHeight_;
            renderer.drawSprite(drawX, drawY, *fieldSprite_);
            drawFieldTypeSpecific(drawX, drawY, field.object_.type(), renderer);
        }
    }
}

void MapExtrinsic::drawFieldTypeSpecific(int x, int y, MapObject::Type type,
                                         Renderer const &renderer) const {
    switch (type) {
        case MapObject::Type::GOLD:
            renderer.drawSprite(x, y, *goldFieldSprite_);
            break;
        case MapObject::Type::ORE:
            renderer.drawSprite(x, y, *woodFieldSprite_);
            break;
        case MapObject::Type::WOOD:
            renderer.drawSprite(x, y, *oreFieldSprite_);
            break;
        case MapObject::Type::NONE:;
    }
}

MapField const &MapExtrinsic::at(int col, int row) {
    return map_.fields()[row - 1][col - 1];
}

void MapExtrinsic::loadMapSprites() {
    auto image = GameData::getImage("grass.png");
    fieldSprite_.reset(new Sprite(fieldWidth_, fieldHeight_, image));
    image = GameData::getImage("gold.png");
    goldFieldSprite_.reset(new Sprite(fieldWidth_, fieldHeight_, image));
    image = GameData::getImage("wood.png");
    woodFieldSprite_.reset(new Sprite(fieldWidth_, fieldHeight_, image));
    image = GameData::getImage("ore.png");
    oreFieldSprite_.reset(new Sprite(fieldWidth_, fieldHeight_, image));
}

void MapExtrinsic::moveCameraBy(Position delta) {
    cameraLeftUpperCorner_.first += delta.first;
    cameraLeftUpperCorner_.second += delta.second;
    cameraLeftUpperCorner_.first =
        std::clamp(cameraLeftUpperCorner_.first, 0, map_.width() - GRID_WIDTH);
    cameraLeftUpperCorner_.second = std::clamp(cameraLeftUpperCorner_.second, 0,
                                               map_.height() - GRID_HEIGHT);
}

Position MapExtrinsic::getCameraPosition() const {
    return cameraLeftUpperCorner_;
}

void MapExtrinsic::accept(MapVisitator *visitator) { visitator->visit(*this); }

int MapExtrinsic::x() const { return x_; }

int MapExtrinsic::y() const { return y_; }

int MapExtrinsic::fieldWidth() const { return fieldWidth_; }

int MapExtrinsic::fieldHeight() const { return fieldHeight_; }