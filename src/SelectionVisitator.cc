#include "GameData.h"
#include "SelectionVisitator.h"

SelectionVisitator::SelectionVisitator(int fieldWidth, int fieldHeight,
                                       Renderer const &renderer)
    : canMoveSprite_(fieldWidth, fieldHeight,
                     GameData::getImage("selected_green.png")),
      cannotMoveSprite_(fieldWidth, fieldHeight,
                        GameData::getImage("selected_red.png")),
      col_{1},
      row_{1},
      visible_{false},
      renderer_(renderer) {}

void SelectionVisitator::visit(MapExtrinsic const &map) {
    auto cameraPos = map.getCameraPosition();
    auto col = col_ - cameraPos.first;
    auto row = row_ - cameraPos.second;
    if (visible_ && col > 0 && col <= GRID_WIDTH && row > 0 &&
        row <= GRID_HEIGHT) {
        renderer_.drawSprite(map.x() + (col - 1) * map.fieldWidth(),
                             map.y() + (row - 1) * map.fieldHeight(),
                             chooseSprite());
    }
}

void SelectionVisitator::visible(bool onOff) { visible_ = onOff; }

void SelectionVisitator::setPosition(int col, int row) {
    col_ = col;
    row_ = row;
}

int SelectionVisitator::col() const { return col_; }

int SelectionVisitator::row() const { return row_; }

void SelectionVisitator::canMove(bool can) { canMove_ = can; }

Sprite const &SelectionVisitator::chooseSprite() {
    if (canMove_) {
        return canMoveSprite_;
    }
    return cannotMoveSprite_;
}