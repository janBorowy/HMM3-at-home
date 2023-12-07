#include "GameData.h"
#include "SelectionVisitator.h"

SelectionVisitator::SelectionVisitator(int fieldWidth, int fieldHeight,
                                       Renderer const &renderer)
    : sprite_(fieldWidth, fieldHeight,
              GameData::getImage("selected_field.png")),
      col_{1},
      row_{1},
      visible_{false},
      renderer_(renderer) {}

void SelectionVisitator::visit(MapExtrinsic const &map) {
    if (visible_) {
        renderer_.drawSprite(map.x() + (col_ - 1) * map.fieldWidth(),
                             map.y() + (row_ - 1) * map.fieldHeight(), sprite_);
    }
}

void SelectionVisitator::visible(bool onOff) { visible_ = onOff; }

void SelectionVisitator::setPosition(int col, int row) {
    col_ = col;
    row_ = row;
}