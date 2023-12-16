#include "GameData.h"
#include "SelectionVisitator.h"

SelectionVisitator::SelectionVisitator(int fieldWidth, int fieldHeight,
                                       const Renderer &renderer)
    : canMoveSprite_(fieldWidth, fieldHeight,
                     GameData::getImage("selected_green.png")),
      cannotMoveSprite_(fieldWidth, fieldHeight,
                        GameData::getImage("selected_red.png")),
      upArrow_(fieldWidth, fieldHeight, GameData::getImage("up_arrow.png")),
      downArrow_(fieldWidth, fieldHeight, GameData::getImage("down_arrow.png")),
      leftArrow_(fieldWidth, fieldHeight, GameData::getImage("left_arrow.png")),
      rightArrow_(fieldWidth, fieldHeight,
                  GameData::getImage("right_arrow.png")),
      col_{1},
      row_{1},
      visible_{false},
      renderer_(renderer) {}

void SelectionVisitator::visit(const MapExtrinsic &map) {
    auto cameraPos = map.getCameraPosition();
    auto col = col_ - cameraPos.first;
    auto row = row_ - cameraPos.second;
    if (visible_) {
        if (canMove_) drawMovementIndicators(map);
        if (col > 0 && col <= GRID_WIDTH && row > 0 && row <= GRID_HEIGHT) {
            renderer_.drawSprite(map.x() + (col - 1) * map.fieldWidth(),
                                 map.y() + (row - 1) * map.fieldHeight(),
                                 chooseSprite());
        }
    }
}

void SelectionVisitator::drawMovementIndicators(const MapExtrinsic &map) {
    auto it = movementIndicators_.begin() +
              1;  // start from second element to avoid drawing over sprite
    while (movementIndicators_.end() - it != 1) {
        auto previous = *it;
        auto next = *(it + 1);
        auto cameraPos = map.getCameraPosition();
        auto col = previous.first - cameraPos.first;
        auto row = previous.second - cameraPos.second;
        Sprite sprite = upArrow_;
        if (previous.first < next.first) {
            sprite = rightArrow_;
        } else if (previous.first > next.first) {
            sprite = leftArrow_;
        } else if (previous.second < next.second) {
            sprite = downArrow_;
        }
        if (col > 0 && col <= GRID_WIDTH && row > 0 && row <= GRID_HEIGHT) {
            renderer_.drawSprite(map.x() + (col - 1) * map.fieldWidth(),
                                 map.y() + (row - 1) * map.fieldHeight(),
                                 sprite);
        }
        ++it;
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

const Sprite &SelectionVisitator::chooseSprite() {
    if (canMove_) {
        return canMoveSprite_;
    }
    return cannotMoveSprite_;
}

void SelectionVisitator::setMovementIndicators(
    const std::vector<Position> &indicators) {
    movementIndicators_ = indicators;
}