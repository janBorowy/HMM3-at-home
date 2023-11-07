#pragma once
#include <memory>
#include "../Renderer.h"
#include "PositionComponent.h"

class GraphicsComponent {
   public:
    virtual ~GraphicsComponent() = default;
    virtual void update(RendererPtr const &renderer,
                        PositionComponentPtr &positionComponent) = 0;
    virtual unsigned int getW() = 0;
    virtual unsigned int getH() = 0;
    virtual GraphicsComponent *clone() const = 0;
};

typedef std::unique_ptr<GraphicsComponent> GraphicsComponentPtr;