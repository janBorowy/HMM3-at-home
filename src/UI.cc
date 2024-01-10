#include "UI.h"

void UI::stepAll() {}
void UI::drawFront(Renderer &renderer) {
    stack_.back()->draw();
#ifdef IMGUI_ON
    stack_.back()->drawImGui();
#endif
}
void UI::pop() { stack_.erase(stack_.end()); }
bool UI::handle(const SDL_Event &event) {
    bool handled = false;
    std::vector<std::shared_ptr<Panel>>::iterator it = stack_.end();
    while (it != stack_.begin() && !handled) {
        --it;
        switch (event.type) {
            case SDL_MOUSEBUTTONDOWN:
                int x, y;
                SDL_GetMouseState(&x, &y);
                handled = (*it)->mouseButtonDown(x, y);
                break;
            case SDL_KEYDOWN:
                handled =
                    (*it)->keyDown(event.key.keysym.sym, event.key.keysym.mod,
                                   !event.key.repeat);
                break;
        }
    }
    // stack.pop_back();

    return handled;
}
void UI::push(Panel *panel) {
    panel->setUI(this);
    stack_.push_back(std::shared_ptr<Panel>(panel));
}

std::shared_ptr<Panel> UI::top() { return *stack_.end(); }
bool UI::isDone() const { return done_; }

void UI::quit() { done_ = true; }
