#pragma once
#include <memory>
#include "../Renderer.h"

class GraphicsComponent {
    public:
    virtual ~GraphicsComponent() = default;
    virtual void update(std::unique_ptr<Renderer> &renderer) = 0;
};