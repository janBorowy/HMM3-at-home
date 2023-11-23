#include "MainPanel.h"

MainPanel::MainPanel() : Panel() {}
void MainPanel::step() {}
void MainPanel::draw(Renderer &renderer) {
    renderer.setColor(255, 0, 0);
    renderer.drawLine(100, 100, 1500, 900);
}
#include <iostream>
bool MainPanel::keyDown(SDL_Keycode key, Uint16 mod, bool isNewPress) {
    if (key == SDLK_e) {
        std::cout << "hello" << std::endl;
        return true;
    }
    return false;
}