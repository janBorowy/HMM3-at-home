#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "GameWindow.h"
#include "MainPanel.h"
#include "UI.h"
#include "engine_core/SdlFacade.h"

void gameLoop();

int main() {
    if (!GameWindow::init()) return 1;
    // Render once to show something other, rather than black window
    GameWindow::step();
    gameLoop();
    GameWindow::quit();
    return 0;
}

void gameLoop() {
    UI panels;
    std::shared_ptr<Renderer> renderer = GameWindow::getRenderer();
    panels.push(new MainPanel);
    while (!panels.isDone()) {
        SDL_Event event;
        SDL_PollEvent(&event);
        if (event.type == SDL_QUIT) {
            panels.quit();
        } else if (panels.handle(event)) {
            // UI handled the event
        }
        renderer->clear();
        panels.drawAll(renderer);
        renderer->swapBuffers();
    }
}