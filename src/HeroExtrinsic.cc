#include "GameData.h"
#include "HeroExtrinsic.h"

HeroExtrinsic::HeroExtrinsic(int initCol, int initRow, MapExtrinsic const &map)
    : hero_(initCol, initRow),
      map_(map),
      sprite_(map.fieldWidth(), map.fieldHeight(),
              GameData::getImage("hero.png")) {}

Hero &HeroExtrinsic::hero() { return hero_; }

void HeroExtrinsic::draw(Renderer const &renderer) const {
    auto pos = hero_.position();
    auto cameraPos = map_.getCameraPosition();
    auto col = pos.first - cameraPos.first;
    auto row = pos.second - cameraPos.second;
    if (col > 0 && col <= GRID_WIDTH && row > 0 && row <= GRID_HEIGHT) {
        renderer.drawSprite(map_.x() + (col - 1) * map_.fieldWidth(),
                            map_.y() + (row - 1) * map_.fieldHeight(), sprite_);
    }
}