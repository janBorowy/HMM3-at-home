#include "GraphicsComponent.h"

class GridComponent : public GraphicsComponent {
    unsigned int square_size_;
    unsigned int rows_;
    unsigned int columns_;

   public:
    GridComponent(unsigned int square_size, unsigned int rows,
                  unsigned int columns);
    virtual ~GridComponent() = default;
    virtual void update(RendererPtr const &renderer,
                        PositionComponentPtr &positionComponent) override;
    virtual unsigned int getW() override;
    virtual unsigned int getH() override;
    virtual GraphicsComponent *clone() const override;
};