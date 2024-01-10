#pragma once
#include <memory>
#include <vector>
#include "Panel.h"
#include "Renderer.h"

// #define IMGUI_ON

struct UI {
    UI() = default;
    void stepAll();
    void drawFront(Renderer &renderer);
    void push(Panel *panel);
    void quit();
    void pop();
    bool handle(const SDL_Event &event);
    bool isDone() const;
    std::shared_ptr<Panel> top();

   private:
    std::vector<std::shared_ptr<Panel>> stack_;
    bool done_;
};