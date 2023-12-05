#include "UI.h"

void UI::stepAll() {}
void UI::drawFront(Renderer &renderer) {
    stack.back()->draw(renderer);
    stack.back()->drawImGui(renderer);
}
void UI::pop() { /*pop pop*/
}
bool UI::handle(SDL_Event const &event) {
    bool handled = false;
    std::vector<std::shared_ptr<Panel>>::iterator it = stack.end();
    while (it != stack.begin() && !handled) {
        --it;
        switch (event.type) {
            case SDL_MOUSEBUTTONDOWN:
                int x, y;
                SDL_GetMouseState(&x, &y);
                handled = (*it)->mouseButtonDown(x, y);
            case SDL_KEYDOWN:
                handled =
                    (*it)->keyDown(event.key.keysym.sym, event.key.keysym.mod,
                                   !event.key.repeat);
                break;
        }
    }
    return handled;
}

void UI::push(Panel *panel) {
    panel->setUI(this);
    stack.push_back(std::shared_ptr<Panel>(panel));
}

bool UI::isDone() const { return done; }

void UI::quit() { done = true; }