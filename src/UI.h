#pragma once
#include <memory>
#include <vector>
#include "Panel.h"
#include "Renderer.h"

struct UI {
    UI() = default;
    void stepAll();
    void drawFront(Renderer &renderer);
    void push(Panel *panel);
    void quit();
    void pop();
    bool handle(const SDL_Event &event);
    bool isDone() const;

   private:
    std::vector<std::shared_ptr<Panel>> stack;
    bool done = false;
};