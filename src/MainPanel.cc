#include "MainPanel.h"

MainPanel::MainPanel() : Panel() {}
void MainPanel::step() {}
void MainPanel::draw(std::shared_ptr<Renderer> renderer) {
    renderer->setColor(255, 0, 0);
    renderer->drawLine(100, 100, 1500, 900);
}
#include <iostream>
bool MainPanel::keyDown(SDL_Keycode key, Uint16 mod, Command const &command,
                        bool isNewPress) {
    if (command.has(Command::SAY_HELLO)) {
        std::cout << "hello" << std::endl;
        return true;
    }
    return false;
}