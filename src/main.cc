#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <chrono>
#include <thread>
#include "GameData.h"
#include "GameWindow.h"
#include "MainPanel.h"
#include "UI.h"

constexpr int FRAMES_PER_SECOND = 60;

void gameLoop();

using SteadyClock = std::chrono::steady_clock;

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

    SteadyClock::time_point frameStart, frameEnd;
    SteadyClock::duration goalFrameDuration =
        std::chrono::seconds(1) / FRAMES_PER_SECOND;
    while (!panels.isDone()) {
        frameStart = SteadyClock::now();

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

        frameEnd = SteadyClock::now();
        SteadyClock::duration sleepDuration = frameEnd - frameStart;

        if (sleepDuration < goalFrameDuration) {
            std::this_thread::sleep_for(sleepDuration);
        }
    }
}