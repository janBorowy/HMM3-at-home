#include "GridComponent.h"

GridComponent::GridComponent(unsigned int square_size, unsigned int rows,
                             unsigned int columns)
    : square_size_(square_size), rows_(rows), columns_(columns) {}

unsigned int GridComponent::getW() { return columns_ * square_size_; }
unsigned int GridComponent::getH() { return rows_ * square_size_; }

void GridComponent::update(RendererPtr const &renderer,
                           PositionComponentPtr &positionComponent) {
    unsigned int x = positionComponent->getX();
    unsigned int y = positionComponent->getY();
    for (int i = 0; i <= rows_; ++i) {
        renderer->drawLine(x, y, x + columns_ * square_size_, y);
        y += square_size_;
    }
    y = positionComponent->getY();
    for (int j = 0; j <= columns_; ++j) {
        renderer->drawLine(x, y, x, y + rows_ * square_size_);
        x += square_size_;
    }
}

GraphicsComponent *GridComponent::clone() const {
    return new GridComponent(square_size_, rows_, columns_);
}
