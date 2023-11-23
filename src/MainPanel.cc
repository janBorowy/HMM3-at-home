#include "MainPanel.h"

MainPanel::MainPanel()
    : Panel(), selectedField("selected_field.png", 50, 50, 100, 100) {}
void MainPanel::step() {}
void MainPanel::draw(Renderer &renderer) { renderer.drawEntity(selectedField); }
#include <iostream>
bool MainPanel::keyDown(SDL_Keycode key, Uint16 mod, bool isNewPress) {
    if (key == SDLK_e) {
        std::cout << "hello" << std::endl;
        return true;
    }
    return false;
}