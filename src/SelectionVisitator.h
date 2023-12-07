#pragma once
#include "MapExtrinsic.h"
#include "MapVisitator.h"
#include "Renderer.h"
#include "Sprite.h"

class SelectionVisitator : public MapVisitator {
    Sprite sprite_;
    unsigned short col_, row_;
    bool visible_;
    Renderer const &renderer_;

   public:
    SelectionVisitator(int fieldWidth, int fieldHeight,
                       Renderer const &renderer);
    virtual void visit(MapExtrinsic const &map) override;
    void visible(bool onOff);
    void setPosition(int col, int row);
};