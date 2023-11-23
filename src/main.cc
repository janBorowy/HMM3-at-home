#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "GameData.h"
#include "GameWindow.h"
#include "MainPanel.h"
#include "UI.h"

void gameLoop();

int main() {
    GameWindow &gameWindow = GameWindow::getInstance();
    // Render once to show something other, rather than black window
    GameData::setRenderer(gameWindow.getRenderer().getSDLRenderer());
    GameData::load();
    gameLoop();
    gameWindow.quit();
    return 0;
}

void gameLoop() {
    UI panels;
    GameWindow &gameWindow = GameWindow::getInstance();
    Renderer &renderer = gameWindow.getRenderer();
    renderer.swapBuffers();
    panels.push(new MainPanel);
    while (!panels.isDone()) {
        SDL_Event event;
        SDL_PollEvent(&event);
        if (event.type == SDL_QUIT) {
            panels.quit();
        } else if (panels.handle(event)) {
            // UI handled the event
        }
        renderer.clear();
        panels.drawAll(renderer);
        renderer.swapBuffers();
    }
}