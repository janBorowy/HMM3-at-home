#pragma once
#include <memory>

class PositionComponent {
    unsigned int x_, y_;

   public:
    PositionComponent();
    PositionComponent(unsigned int x, unsigned int y);
    void setX(unsigned int x);
    void setY(unsigned int y);
    unsigned int getX();
    unsigned int getY();
};

typedef std::unique_ptr<PositionComponent> PositionComponentPtr;