#pragma once
#include "MapExtrinsic.h"
#include "MapVisitator.h"
#include "Renderer.h"
#include "Sprite.h"

class SelectionVisitator : public MapVisitator {
    Sprite canMoveSprite_;
    Sprite cannotMoveSprite_;
    Sprite upArrow_;
    Sprite downArrow_;
    Sprite leftArrow_;
    Sprite rightArrow_;
    unsigned short col_, row_;
    bool visible_;
    bool canMove_;
    const Renderer &renderer_;
    std::vector<Position> movementIndicators_;
    void drawMovementIndicators(const MapExtrinsic &map);
    const Sprite &chooseSprite();

   public:
    SelectionVisitator(int fieldWidth, int fieldHeight,
                       const Renderer &renderer);
    virtual void visit(const MapExtrinsic &map) override;
    void visible(bool onOff);
    void setPosition(int col, int row);
    int col() const;
    int row() const;
    void canMove(bool can);
    void setMovementIndicators(const std::vector<Position> &indicators);
};