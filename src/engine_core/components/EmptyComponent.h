#pragma once
#include "GraphicsComponent.h"

class EmptyComponent : public GraphicsComponent {
    unsigned width_;
    unsigned height_;

   public:
    EmptyComponent();
    EmptyComponent(unsigned width, unsigned height);
    virtual ~EmptyComponent() = default;
    virtual void update(RendererPtr const &renderer,
                        PositionComponentPtr &positionComponent);
    virtual unsigned int getW();
    virtual unsigned int getH();
};