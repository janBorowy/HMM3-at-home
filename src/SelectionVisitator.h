#pragma once
#include "MapExtrinsic.h"
#include "MapVisitator.h"
#include "Renderer.h"
#include "Sprite.h"

class SelectionVisitator : public MapVisitator {
    Sprite canMoveSprite_;
    Sprite cannotMoveSprite_;
    unsigned short col_, row_;
    bool visible_;
    bool canMove_;
    Renderer const &renderer_;

    Sprite const &chooseSprite();

   public:
    SelectionVisitator(int fieldWidth, int fieldHeight,
                       Renderer const &renderer);
    virtual void visit(MapExtrinsic const &map) override;
    void visible(bool onOff);
    void setPosition(int col, int row);
    int col() const;
    int row() const;
    void canMove(bool can);
};