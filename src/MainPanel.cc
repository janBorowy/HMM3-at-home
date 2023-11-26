#include "MainPanel.h"

MainPanel::MainPanel() : Panel(), mapGrid_(50, 50, 1000, 896) {}
void MainPanel::step() {}
void MainPanel::draw(Renderer const &renderer) {
    mapGrid_.drawFields(renderer);
}
#include <iostream>
bool MainPanel::keyDown(SDL_Keycode key, Uint16 mod, bool isNewPress) {
    if (key == SDLK_e) {
        std::cout << "hello" << std::endl;
        return true;
    }
    return false;
}