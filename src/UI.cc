#include "UI.h"

void UI::stepAll() {}
void UI::drawAll(std::shared_ptr<Renderer> renderer) {
    stack.back()->draw(renderer);
}
void UI::pop() { /*pop pop*/
}
bool UI::handle(SDL_Event const &event) {
    bool handled = false;
    std::vector<std::shared_ptr<Panel>>::iterator it = stack.end();
    while (it != stack.begin() && !handled) {
        --it;
        switch (event.type) {
            case SDL_KEYDOWN:
                Command command(event.key.keysym.sym);
                handled =
                    (*it)->keyDown(event.key.keysym.sym, event.key.keysym.mod,
                                   command, !event.key.repeat);
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