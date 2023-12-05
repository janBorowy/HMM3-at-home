#include "GameData.h"
#include "MapExtrinsic.h"

MapExtrinsic::MapExtrinsic(unsigned short initX, unsigned short initY,
                           unsigned short width, unsigned short height)
    : x_{initX},
      y_{initY},
      fieldHeight_(height / GRID_HEIGHT),
      fieldWidth_(width / GRID_WIDTH),
      selectedRow_{0},
      selectedCol_{0},
      map_{} {
    auto image = GameData::getImage("empty_field.png");
    fieldSprite_.reset(new Sprite(fieldWidth_, fieldHeight_, image));
    image = GameData::getImage("gold.png");
    goldFieldSprite_.reset(new Sprite(fieldWidth_, fieldHeight_, image));
    map_.placeObject(10, 10, MapObject(MapObject::GOLD, 1000));
}

void MapExtrinsic::drawFields(Renderer const &renderer) const {
    for (int row = 0; row < 16; ++row) {
        for (int col = 0; col < 16; ++col) {
            auto &field = map_.fields()[row][col];
            renderer.drawSprite(x_ + col * fieldWidth_, y_ + row * fieldHeight_,
                                *fieldSprite_);
            drawFieldTypeSpecific(x_ + col * fieldWidth_,
                                  y_ + row * fieldHeight_, field.object_.type(),
                                  renderer);
        }
    }
}

void MapExtrinsic::drawFieldTypeSpecific(int x, int y, MapObject::Type type,
                                         Renderer const &renderer) const {
    switch (type) {
        case MapObject::Type::GOLD:
            renderer.drawSprite(x, y, *goldFieldSprite_);
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