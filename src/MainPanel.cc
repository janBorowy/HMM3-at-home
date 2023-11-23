#include "MainPanel.h"

MainPanel::MainPanel() : Panel() {}
void MainPanel::step() {}
void MainPanel::draw(Renderer &renderer) {}
#include <iostream>
bool MainPanel::keyDown(SDL_Keycode key, Uint16 mod, bool isNewPress) {
    if (key == SDLK_e) {
        std::cout << "hello" << std::endl;
        return true;
    }
    return false;
}