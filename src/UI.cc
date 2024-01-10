#include "UI.h"

void UI::stepAll() {}
void UI::drawFront(Renderer &renderer) {
    stack.at(panel_num)->draw();
    stack.at(panel_num)->drawImGui();
}
void UI::pop() { /*pop pop*/
}
bool UI::handle(const SDL_Event &event) {
    bool handled = false;
    // std::vector<std::shared_ptr<Panel>>::iterator it = stack.end();
    //  while (it != stack.begin() && !handled) {
    //--it;
    switch (event.type) {
        case SDL_MOUSEBUTTONDOWN:
            int x, y;
            SDL_GetMouseState(&x, &y);
            handled = stack.at(panel_num)->mouseButtonDown(x, y);
            break;
        case SDL_KEYDOWN:
            handled = stack.at(panel_num)->keyDown(
                event.key.keysym.sym, event.key.keysym.mod, !event.key.repeat);
            break;
    }
    // stack.pop_back();

    return handled;
}
void UI::push(Panel *panel) {
    panel->setUI(this);
    stack.push_back(std::shared_ptr<Panel>(panel));
    panel_num = stack.size() - 1;
}

bool UI::isDone() const { return done; }

void UI::quit() { done = true; }

int UI::getPanelNum() { return panel_num; }
void UI::setPanelNum(int num) { panel_num = num; }

std::shared_ptr<Panel> &UI::at(int num) { return stack.at(num); }