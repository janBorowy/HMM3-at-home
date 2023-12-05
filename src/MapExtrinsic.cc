#include <algorithm>
#include "GameData.h"
#include "MapExtrinsic.h"

MapExtrinsic::MapExtrinsic(unsigned short initX, unsigned short initY,
                           unsigned short width, unsigned short height)
    : x_{initX},
      y_{initY},
      fieldHeight_(height / GRID_HEIGHT),
      fieldWidth_(width / GRID_WIDTH),
      map_{},
      cameraLeftUpperCorner{0, 0} {
    loadMapSprites();
    map_.placeObject(10, 10, MapObject(MapObject::GOLD, 1000));
    map_.placeObject(11, 10, MapObject(MapObject::WOOD, 1000));
    map_.placeObject(12, 10, MapObject(MapObject::ORE, 1000));
}

void MapExtrinsic::drawFields(Renderer const &renderer) const {
    for (int row = cameraLeftUpperCorner.second;
         row < 16 + cameraLeftUpperCorner.second; ++row) {
        for (int col = cameraLeftUpperCorner.first;
             col < 16 + cameraLeftUpperCorner.first; ++col) {
            auto &field = map_.fields()[row][col];
            int drawX = x_ + (col - cameraLeftUpperCorner.first) * fieldWidth_;
            int drawY =
                y_ + (row - cameraLeftUpperCorner.second) * fieldHeight_;
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

void MapExtrinsic::handleClick(int x, int y) {
    // auto clickedCol = (x - x_) / fieldWidth_ + 1;
    // auto clickedRow = (y - y_) / fieldHeight_ + 1;
    // at(selectedCol_, selectedRow_).changeSprite("empty_field.png");
    // selectedCol_ = clickedCol;
    // selectedRow_ = clickedRow;
    // at(clickedCol, clickedRow).changeSprite("selected_field.png");
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
    cameraLeftUpperCorner.first =
        std::clamp(cameraLeftUpperCorner.first, 0, MAP_WIDTH);
    cameraLeftUpperCorner.second =
        std::clamp(cameraLeftUpperCorner.second, 0, MAP_HEIGHT);
    cameraLeftUpperCorner.first += delta.first;
    cameraLeftUpperCorner.second += delta.second;
}