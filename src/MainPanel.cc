#include "MainPanel.h"

constexpr int GRID_X = 50;
constexpr int GRID_Y = 50;
constexpr int GRID_PANEL_WIDTH = 1000;
constexpr int GRID_PANEL_HEIGHT = 896;

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

bool MainPanel::mouseButtonDown(int x, int y) {
    // TODO: maybe get element detection better somehow
    if (x > GRID_X && x < GRID_X + GRID_PANEL_WIDTH && y > GRID_Y &&
        y < GRID_Y + GRID_PANEL_HEIGHT) {
        mapGrid_.handleClick(x, y);
        return true;
    }
    return false;
}