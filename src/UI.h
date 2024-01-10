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
    int getPanelNum();
    void setPanelNum(int num);
    std::shared_ptr<Panel> &at(int num);

   private:
    std::vector<std::shared_ptr<Panel>> stack;
    bool done = false;
    int panel_num;
};