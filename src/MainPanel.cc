#include "MainPanel.h"

constexpr int GRID_X = 50;
constexpr int GRID_Y = 50;
constexpr int GRID_PANEL_WIDTH = 1000;
constexpr int GRID_PANEL_HEIGHT = 896;

MainPanel::MainPanel() : Panel() {}
void MainPanel::step() {}
void MainPanel::draw(Renderer const &renderer) {}
#include <iostream>
bool MainPanel::keyDown(SDL_Keycode key, Uint16 mod, bool isNewPress) {
    if (key == SDLK_e) {
        std::cout << "hello" << std::endl;
        return true;
    }
    return false;
}

bool MainPanel::mouseButtonDown(int x, int y) { return false; }